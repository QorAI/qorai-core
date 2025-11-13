/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_wallet/browser/qorai_wallet_p3a.h"

#include <algorithm>
#include <optional>
#include <string>
#include <utility>

#include "base/check.h"
#include "base/check_op.h"
#include "base/command_line.h"
#include "base/logging.h"
#include "base/metrics/histogram_functions.h"
#include "base/metrics/histogram_macros.h"
#include "base/notreached.h"
#include "base/strings/string_number_conversions.h"
#include "base/time/time.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/keyring_service.h"
#include "qorai/components/qorai_wallet/browser/pref_names.h"
#include "qorai/components/qorai_wallet/browser/tx_service.h"
#include "qorai/components/qorai_wallet/common/common_utils.h"
#include "qorai/components/p3a_utils/bucket.h"
#include "qorai/components/p3a_utils/feature_usage.h"
#include "components/prefs/pref_service.h"
#include "components/prefs/scoped_user_pref_update.h"

namespace qorai_wallet {

namespace {

const int kRefreshP3AFrequencyHours = 24;
const int kActiveAccountBuckets[] = {0, 1, 2, 3, 7};
const int kNFTCountBuckets[] = {0, 4, 20};
constexpr base::TimeDelta kOnboardingRecordDelay = base::Seconds(120);

// Has the Wallet keyring been created?
// 0) No, 1) Yes
void RecordKeyringCreated(bool created) {
  UMA_HISTOGRAM_BOOLEAN(kKeyringCreatedHistogramName,
                        static_cast<int>(created));
}

}  // namespace

QoraiWalletP3A::QoraiWalletP3A(QoraiWalletService* wallet_service,
                               KeyringService* keyring_service,
                               TxService* tx_service,
                               PrefService* profile_prefs,
                               PrefService* local_state)
    : wallet_service_(wallet_service),
      keyring_service_(keyring_service),
      tx_service_(tx_service),
      profile_prefs_(profile_prefs),
      local_state_(local_state) {
  DCHECK(profile_prefs);
  DCHECK(local_state);

  RecordInitialQoraiWalletP3AState();
  AddObservers();

  local_state_change_registrar_.Init(local_state_);
  local_state_change_registrar_.Add(
      kQoraiWalletLastUnlockTime,
      base::BindRepeating(&QoraiWalletP3A::ReportUsage, base::Unretained(this),
                          true));
  profile_pref_change_registrar_.Init(profile_prefs_);
  profile_pref_change_registrar_.Add(
      kQoraiWalletNftDiscoveryEnabled,
      base::BindRepeating(&QoraiWalletP3A::ReportNftDiscoverySetting,
                          base::Unretained(this)));

  // try to record the onboarding histogram
  // just in the case the user quit the app
  // before the 120 second deadline in the last
  // app session
  RecordOnboardingHistogram();

  ReportNftDiscoverySetting();
}

QoraiWalletP3A::QoraiWalletP3A() = default;

QoraiWalletP3A::~QoraiWalletP3A() = default;

void QoraiWalletP3A::AddObservers() {
  keyring_service_->AddObserver(
      keyring_service_observer_receiver_.BindNewPipeAndPassRemote());
  tx_service_->AddObserver(
      tx_service_observer_receiver_.BindNewPipeAndPassRemote());
  update_timer_.Start(FROM_HERE, base::Hours(kRefreshP3AFrequencyHours), this,
                      &QoraiWalletP3A::OnUpdateTimerFired);
  OnUpdateTimerFired();  // Also call on startup
}

void QoraiWalletP3A::Bind(
    mojo::PendingReceiver<mojom::QoraiWalletP3A> receiver) {
  receivers_.Add(this, std::move(receiver));
}

void QoraiWalletP3A::ReportUsage(bool unlocked) {
  VLOG(1) << "Wallet P3A: starting report";
  base::Time wallet_last_used =
      local_state_->GetTime(kQoraiWalletLastUnlockTime);

  if (unlocked) {
    p3a_utils::RecordFeatureUsage(local_state_, kQoraiWalletP3AFirstUnlockTime,
                                  kQoraiWalletP3ALastUnlockTime);
    WriteUsageStatsToHistogram();
  } else {
    // Maybe record existing timestamp in case the user is not new.
    p3a_utils::MaybeRecordFeatureExistingUsageTimestamp(
        local_state_, kQoraiWalletP3AFirstUnlockTime,
        kQoraiWalletP3ALastUnlockTime, wallet_last_used);
  }

  p3a_utils::RecordFeatureNewUserReturning(
      local_state_, kQoraiWalletP3AFirstUnlockTime,
      kQoraiWalletP3ALastUnlockTime, kQoraiWalletP3AUsedSecondDay,
      kQoraiWalletNewUserReturningHistogramName);
  p3a_utils::RecordFeatureLastUsageTimeMetric(
      local_state_, kQoraiWalletP3ALastUnlockTime,
      kQoraiWalletLastUsageTimeHistogramName);

  ReportNftDiscoverySetting();
}

void QoraiWalletP3A::ReportJSProvider(mojom::JSProviderType provider_type,
                                      mojom::CoinType coin_type,
                                      bool allow_provider_overwrite) {
  CHECK(coin_type == mojom::CoinType::ETH || coin_type == mojom::CoinType::SOL);

  const char* histogram_name;
  switch (coin_type) {
    case mojom::CoinType::ETH:
      histogram_name = kEthProviderHistogramName;
      break;
    case mojom::CoinType::SOL:
      histogram_name = kSolProviderHistogramName;
      break;
    default:
      return;
  }

  JSProviderAnswer answer = JSProviderAnswer::kNoWallet;
  bool is_wallet_setup = std::ranges::any_of(
      keyring_service_->GetAllAccountInfos(), [coin_type](auto& account) {
        return account->account_id->coin == coin_type;
      });

  switch (provider_type) {
    case mojom::JSProviderType::None:
      if (is_wallet_setup) {
        answer = JSProviderAnswer::kWalletDisabled;
      } else {
        answer = JSProviderAnswer::kNoWallet;
      }
      break;
    case mojom::JSProviderType::ThirdParty:
      // Third-party overriding is considered if the native wallet
      // is enabled and the native wallet is setup.
      answer = is_wallet_setup && allow_provider_overwrite
                   ? JSProviderAnswer::kThirdPartyOverriding
                   : JSProviderAnswer::kThirdPartyNotOverriding;
      break;
    case mojom::JSProviderType::Native:
      if (is_wallet_setup) {
        // A native wallet is definitely not being overridden
        // if provider overwrites are allowed.
        answer = !allow_provider_overwrite
                     ? JSProviderAnswer::kNativeOverridingDisallowed
                     : JSProviderAnswer::kNativeNotOverridden;
      }
      break;
  }

  base::UmaHistogramEnumeration(histogram_name, answer);
}

std::optional<mojom::OnboardingAction>
QoraiWalletP3A::GetLastOnboardingAction() {
  if (local_state_->HasPrefPath(kQoraiWalletP3AOnboardingLastStep)) {
    int pref_value =
        local_state_->GetInteger(kQoraiWalletP3AOnboardingLastStep);
    return static_cast<mojom::OnboardingAction>(pref_value);
  }
  return std::nullopt;
}

void QoraiWalletP3A::ReportOnboardingAction(mojom::OnboardingAction action) {
  if (action == mojom::OnboardingAction::StartRestore) {
    // We do not want to monitor wallet restores; cancel the
    // histogram record timer and wipe out the last onboarding step.
    local_state_->ClearPref(kQoraiWalletP3AOnboardingLastStep);
    onboarding_report_timer_.Stop();
    return;
  }
  std::optional<mojom::OnboardingAction> last_step = GetLastOnboardingAction();
  if (!last_step.has_value() || *last_step < action) {
    // Only record steps that are ahead of the previous step so we
    // don't record back navigation.
    local_state_->SetInteger(kQoraiWalletP3AOnboardingLastStep,
                             static_cast<int>(action));
  }
  if (onboarding_report_timer_.IsRunning() ||
      action == mojom::OnboardingAction::Shown) {
    // If the event is the first possible action (aka the shown event),
    // or if timer is already running (re)start the timer to debounce.
    onboarding_report_timer_.Start(
        FROM_HERE, kOnboardingRecordDelay,
        base::BindOnce(&QoraiWalletP3A::RecordOnboardingHistogram,
                       base::Unretained(this)));
  } else {
    // If the timer is not running and the action is after the first possible
    // event, report it right away since it probably missed the 120 sec
    // deadline.
    RecordOnboardingHistogram();
  }
}

void QoraiWalletP3A::RecordOnboardingHistogram() {
  std::optional<mojom::OnboardingAction> last_step = GetLastOnboardingAction();
  if (!last_step.has_value()) {
    return;
  }
  local_state_->ClearPref(kQoraiWalletP3AOnboardingLastStep);
  UMA_HISTOGRAM_ENUMERATION(kOnboardingConversionHistogramName, *last_step);
}

void QoraiWalletP3A::ReportTransactionSent(mojom::CoinType coin,
                                           bool new_send) {
  const char* histogram_name = nullptr;
  switch (coin) {
    case mojom::CoinType::ETH:
      histogram_name = kEthTransactionSentHistogramName;
      break;
    case mojom::CoinType::SOL:
      histogram_name = kSolTransactionSentHistogramName;
      break;
    case mojom::CoinType::FIL:
      histogram_name = kFilTransactionSentHistogramName;
      break;
    case mojom::CoinType::BTC:
      histogram_name = kBtcTransactionSentHistogramName;
      break;
    case mojom::CoinType::ZEC:
      histogram_name = kZecTransactionSentHistogramName;
      break;
    case mojom::CoinType::ADA:
      // TODO(https://github.com/qorai/qorai-browser/issues/49535): Cardano P3A
      return;
    case mojom::CoinType::DOT:
      // TODO(https://github.com/qorai/qorai-browser/issues/49536): Polkadot P3A
      return;
  }

  CHECK(histogram_name);

  ScopedDictPrefUpdate last_sent_time_update(
      profile_prefs_, kQoraiWalletLastTransactionSentTimeDict);
  base::Value::Dict& last_sent_time_dict = last_sent_time_update.Get();

  std::string coin_key = base::NumberToString(static_cast<int>(coin));

  base::Time now = base::Time::Now();
  base::Time last_sent_time = base::Time::FromSecondsSinceUnixEpoch(
      last_sent_time_dict.FindDouble(coin_key).value_or(0.0));

  if (!new_send && last_sent_time.is_null()) {
    // Don't report if a transaction was never sent.
    return;
  }
  int answer = 0;
  if (new_send || (now - last_sent_time) < base::Days(7)) {
    answer = 1;
  }
  if (new_send) {
    last_sent_time_dict.Set(coin_key, now.InSecondsFSinceUnixEpoch());
  }

  base::UmaHistogramExactLinear(histogram_name, answer, 2);
}

void QoraiWalletP3A::RecordActiveWalletCount(int count,
                                             mojom::CoinType coin_type) {
  DCHECK_GE(count, 0);
  const char* histogram_name = nullptr;

  switch (coin_type) {
    case mojom::CoinType::ETH:
      histogram_name = kEthActiveAccountHistogramName;
      break;
    case mojom::CoinType::SOL:
      histogram_name = kSolActiveAccountHistogramName;
      break;
    case mojom::CoinType::FIL:
      histogram_name = kFilActiveAccountHistogramName;
      break;
    case mojom::CoinType::BTC:
      histogram_name = kBtcActiveAccountHistogramName;
      break;
    case mojom::CoinType::ZEC:
      histogram_name = kZecActiveAccountHistogramName;
      break;
    case mojom::CoinType::ADA:
      // TODO(https://github.com/qorai/qorai-browser/issues/49535): Cardano P3A
      return;
    case mojom::CoinType::DOT:
      // TODO(https://github.com/qorai/qorai-browser/issues/49536): Polkadot P3A
      return;
  }

  CHECK(histogram_name);

  const base::Value::Dict& active_wallet_dict =
      profile_prefs_->GetDict(kQoraiWalletP3AActiveWalletDict);
  std::string coin_type_str = base::NumberToString(static_cast<int>(coin_type));
  if (!active_wallet_dict.FindBool(coin_type_str).has_value()) {
    if (count == 0) {
      // Should not record zero to histogram if user never had an active
      // account, to avoid sending unnecessary data.
      return;
    }
    ScopedDictPrefUpdate active_wallet_dict_update(
        profile_prefs_, kQoraiWalletP3AActiveWalletDict);
    active_wallet_dict_update->Set(coin_type_str, true);
  }
  p3a_utils::RecordToHistogramBucket(histogram_name, kActiveAccountBuckets,
                                     count);

  if (count > 0) {
    MaybeRecordNewUserBalance();
  }
}

void QoraiWalletP3A::RecordNFTGalleryView(int nft_count) {
  if (!local_state_->GetBoolean(kQoraiWalletP3ANFTGalleryUsed)) {
    local_state_->SetBoolean(kQoraiWalletP3ANFTGalleryUsed, true);
    UMA_HISTOGRAM_BOOLEAN(kQoraiWalletNFTNewUserHistogramName, true);
  }
  p3a_utils::RecordToHistogramBucket(kQoraiWalletNFTCountHistogramName,
                                     kNFTCountBuckets, nft_count);
}

void QoraiWalletP3A::MaybeRecordNewUserBalance() {
  base::Time deadline = base::Time::Now() - base::Days(7);
  if (local_state_->GetTime(kQoraiWalletP3AFirstUnlockTime) >= deadline &&
      !local_state_->GetBoolean(kQoraiWalletP3ANewUserBalanceReported)) {
    UMA_HISTOGRAM_BOOLEAN(kNewUserBalanceHistogramName, true);
    local_state_->SetBoolean(kQoraiWalletP3ANewUserBalanceReported, true);
  }
}

void QoraiWalletP3A::ReportNftDiscoverySetting() {
  if (!local_state_->GetTime(kQoraiWalletLastUnlockTime).is_null()) {
    UMA_HISTOGRAM_BOOLEAN(
        kQoraiWalletNFTDiscoveryEnabledHistogramName,
        profile_prefs_->GetBoolean(kQoraiWalletNftDiscoveryEnabled));
  }
}

void QoraiWalletP3A::OnUpdateTimerFired() {
  ReportUsage(false);
  for (const auto& coin : GetEnabledCoins()) {
    ReportTransactionSent(coin, false);
  }
}

void QoraiWalletP3A::WriteUsageStatsToHistogram() {
  VLOG(1) << "Wallet P3A: Recording usage";
  UMA_HISTOGRAM_BOOLEAN(kQoraiWalletMonthlyHistogramName, true);
  UMA_HISTOGRAM_BOOLEAN(kQoraiWalletWeeklyHistogramName, true);
  UMA_HISTOGRAM_BOOLEAN(kQoraiWalletDailyHistogramName, true);
}

void QoraiWalletP3A::RecordInitialQoraiWalletP3AState() {
  RecordKeyringCreated(keyring_service_->IsWalletCreatedSync());
}

// KeyringServiceObserver
void QoraiWalletP3A::WalletCreated() {
  RecordKeyringCreated(keyring_service_->IsWalletCreatedSync());
}

void QoraiWalletP3A::OnTransactionStatusChanged(
    mojom::TransactionInfoPtr tx_info) {
  if (tx_info->tx_status != mojom::TransactionStatus::Approved) {
    return;
  }

  auto tx_coin = GetCoinTypeFromTxDataUnion(*tx_info->tx_data_union);
  auto tx_type = tx_info->tx_type;
  auto count_test_networks = base::CommandLine::ForCurrentProcess()->HasSwitch(
      qorai_wallet::mojom::kP3ACountTestNetworksSwitch);
  auto chain_id = tx_info->chain_id;

  if (tx_coin == mojom::CoinType::ETH) {
    if (tx_type != mojom::TransactionType::ETHSend &&
        tx_type != mojom::TransactionType::ERC20Transfer) {
      return;
    }
    if (!count_test_networks &&
        (chain_id == mojom::kSepoliaChainId ||
         chain_id == mojom::kLocalhostChainId ||
         chain_id == mojom::kFilecoinEthereumTestnetChainId)) {
      return;
    }
  } else if (tx_coin == mojom::CoinType::FIL) {
    if (tx_type != mojom::TransactionType::Other) {
      return;
    }
    if (!count_test_networks && (chain_id == mojom::kFilecoinTestnet ||
                                 chain_id == mojom::kLocalhostChainId)) {
      return;
    }
  } else if (tx_coin == mojom::CoinType::SOL) {
    if (tx_type != mojom::TransactionType::SolanaSystemTransfer &&
        tx_type != mojom::TransactionType::SolanaSPLTokenTransfer &&
        tx_type !=
            mojom::TransactionType::
                SolanaSPLTokenTransferWithAssociatedTokenAccountCreation) {
      return;
    }
    if (!count_test_networks && (chain_id == mojom::kSolanaTestnet ||
                                 chain_id == mojom::kSolanaDevnet ||
                                 chain_id == mojom::kLocalhostChainId)) {
      return;
    }
  } else if (tx_coin == mojom::CoinType::BTC) {
    if (tx_type != mojom::TransactionType::Other) {
      return;
    }
    if (!count_test_networks && chain_id == mojom::kBitcoinTestnet) {
      return;
    }
  } else if (tx_coin == mojom::CoinType::ZEC) {
    if (tx_type != mojom::TransactionType::Other) {
      return;
    }
    if (!count_test_networks && chain_id == mojom::kZCashTestnet) {
      return;
    }
  } else if (tx_coin == mojom::CoinType::ADA) {
    if (tx_type != mojom::TransactionType::Other) {
      return;
    }
    if (!count_test_networks && chain_id == mojom::kCardanoTestnet) {
      return;
    }
  } else {
    NOTREACHED() << tx_coin;
  }
  ReportTransactionSent(tx_coin, true);
}

}  // namespace qorai_wallet
