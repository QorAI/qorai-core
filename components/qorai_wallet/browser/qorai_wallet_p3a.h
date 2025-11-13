/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_QORAI_WALLET_P3A_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_QORAI_WALLET_P3A_H_

#include <optional>

#include "base/gtest_prod_util.h"
#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_wallet/browser/keyring_service_observer_base.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "components/prefs/pref_change_registrar.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/receiver_set.h"

class PrefService;

namespace qorai_wallet {

// TODO(https://github.com/qorai/qorai-browser/issues/45278): Cardano P3A
inline constexpr char kKeyringCreatedHistogramName[] =
    "Qorai.Wallet.KeyringCreated";
inline constexpr char kOnboardingConversionHistogramName[] =
    "Qorai.Wallet.OnboardingConversion.3";
inline constexpr char kNewUserBalanceHistogramName[] =
    "Qorai.Wallet.NewUserBalance";
inline constexpr char kEthProviderHistogramName[] =
    "Qorai.Wallet.EthProvider.4";
inline constexpr char kSolProviderHistogramName[] =
    "Qorai.Wallet.SolProvider.2";
inline constexpr char kEthTransactionSentHistogramName[] =
    "Qorai.Wallet.EthTransactionSent";
inline constexpr char kSolTransactionSentHistogramName[] =
    "Qorai.Wallet.SolTransactionSent";
inline constexpr char kFilTransactionSentHistogramName[] =
    "Qorai.Wallet.FilTransactionSent";
inline constexpr char kBtcTransactionSentHistogramName[] =
    "Qorai.Wallet.BtcTransactionSent";
inline constexpr char kZecTransactionSentHistogramName[] =
    "Qorai.Wallet.ZecTransactionSent";
inline constexpr char kEthActiveAccountHistogramName[] =
    "Qorai.Wallet.ActiveEthAccounts";
inline constexpr char kSolActiveAccountHistogramName[] =
    "Qorai.Wallet.ActiveSolAccounts";
inline constexpr char kFilActiveAccountHistogramName[] =
    "Qorai.Wallet.ActiveFilAccounts";
inline constexpr char kBtcActiveAccountHistogramName[] =
    "Qorai.Wallet.ActiveBtcAccounts";
inline constexpr char kZecActiveAccountHistogramName[] =
    "Qorai.Wallet.ActiveZecAccounts";
inline constexpr char kQoraiWalletDailyHistogramName[] =
    "Qorai.Wallet.UsageDaily";
inline constexpr char kQoraiWalletWeeklyHistogramName[] =
    "Qorai.Wallet.UsageWeekly";
inline constexpr char kQoraiWalletMonthlyHistogramName[] =
    "Qorai.Wallet.UsageMonthly";
inline constexpr char kQoraiWalletNewUserReturningHistogramName[] =
    "Qorai.Wallet.NewUserReturning";
inline constexpr char kQoraiWalletLastUsageTimeHistogramName[] =
    "Qorai.Wallet.LastUsageTime";
inline constexpr char kQoraiWalletNFTCountHistogramName[] =
    "Qorai.Wallet.NFTCount";
inline constexpr char kQoraiWalletNFTNewUserHistogramName[] =
    "Qorai.Wallet.NFTNewUser";
inline constexpr char kQoraiWalletNFTDiscoveryEnabledHistogramName[] =
    "Qorai.Wallet.NFTDiscoveryEnabled";

class QoraiWalletService;
class KeyringService;
class TxService;

enum class JSProviderAnswer {
  kNoWallet = 0,
  kWalletDisabled = 1,
  kNativeNotOverridden = 2,
  kNativeOverridingDisallowed = 3,
  kThirdPartyNotOverriding = 4,
  kThirdPartyOverriding = 5,
  kMaxValue = kThirdPartyOverriding
};

// Reports QoraiWallet related P3A data
class QoraiWalletP3A : public KeyringServiceObserverBase,
                       public mojom::QoraiWalletP3A,
                       public mojom::TxServiceObserver {
 public:
  QoraiWalletP3A(QoraiWalletService* wallet_service,
                 KeyringService* keyring_service,
                 TxService* tx_service,
                 PrefService* profile_prefs,
                 PrefService* local_state);

  // For testing
  QoraiWalletP3A();

  ~QoraiWalletP3A() override;
  QoraiWalletP3A(const QoraiWalletP3A&) = delete;
  QoraiWalletP3A& operator=(QoraiWalletP3A&) = delete;

  void Bind(mojo::PendingReceiver<mojom::QoraiWalletP3A> receiver);

  void AddObservers();

  void ReportUsage(bool unlocked);
  void ReportJSProvider(mojom::JSProviderType provider_type,
                        mojom::CoinType coin_type,
                        bool allow_provider_overwrite) override;
  void ReportOnboardingAction(mojom::OnboardingAction action) override;
  void RecordActiveWalletCount(int count, mojom::CoinType coin_type) override;
  void RecordNFTGalleryView(int nft_count) override;

  // KeyringServiceObserverBase:
  void WalletCreated() override;

  // mojom::TxServiceObserver:
  void OnNewUnapprovedTx(mojom::TransactionInfoPtr tx_info) override {}
  void OnUnapprovedTxUpdated(mojom::TransactionInfoPtr tx_info) override {}
  void OnTransactionStatusChanged(mojom::TransactionInfoPtr tx_info) override;
  void OnTxServiceReset() override {}

 private:
  FRIEND_TEST_ALL_PREFIXES(QoraiWalletP3AUnitTest, ReportTransactionSent);
  friend class QoraiWalletP3AUnitTest;

  void OnUpdateTimerFired();
  void WriteUsageStatsToHistogram();
  void RecordInitialQoraiWalletP3AState();
  std::optional<mojom::OnboardingAction> GetLastOnboardingAction();
  void RecordOnboardingHistogram();
  void MaybeRecordNewUserBalance();
  void ReportNftDiscoverySetting();
  void ReportTransactionSent(mojom::CoinType coin, bool new_send);
  raw_ptr<QoraiWalletService> wallet_service_;
  raw_ptr<KeyringService> keyring_service_;
  raw_ptr<TxService> tx_service_;
  raw_ptr<PrefService> profile_prefs_;
  raw_ptr<PrefService> local_state_;

  mojo::Receiver<mojom::KeyringServiceObserver>
      keyring_service_observer_receiver_{this};

  mojo::Receiver<mojom::TxServiceObserver> tx_service_observer_receiver_{this};

  base::OneShotTimer onboarding_report_timer_;

  mojo::ReceiverSet<mojom::QoraiWalletP3A> receivers_;
  base::RepeatingTimer update_timer_;
  PrefChangeRegistrar local_state_change_registrar_;
  PrefChangeRegistrar profile_pref_change_registrar_;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_QORAI_WALLET_P3A_H_
