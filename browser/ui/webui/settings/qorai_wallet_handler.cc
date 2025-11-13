/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/settings/qorai_wallet_handler.h"

#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "base/check.h"
#include "base/check_op.h"
#include "base/functional/bind.h"
#include "base/json/json_writer.h"
#include "base/values.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "qorai/components/qorai_wallet/browser/blockchain_registry.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_utils.h"
#include "qorai/components/qorai_wallet/browser/json_rpc_service.h"
#include "qorai/components/qorai_wallet/browser/pref_names.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/components/qorai_wallet/common/common_utils.h"
#include "qorai/components/qorai_wallet/common/value_conversion_utils.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/web_ui.h"
#include "ui/base/l10n/l10n_util.h"

namespace {

base::Value::Dict MakeSelectValue(const std::u16string& name,
                                  ::qorai_wallet::mojom::DefaultWallet value) {
  base::Value::Dict item;
  item.Set("value", static_cast<int>(value));
  item.Set("name", name);
  return item;
}

base::Value::Dict MakeSelectValue(
    const std::u16string& name,
    ::qorai_wallet::mojom::BlowfishOptInStatus value) {
  base::Value::Dict item;
  item.Set("value", static_cast<int>(value));
  item.Set("name", name);
  return item;
}

std::optional<qorai_wallet::mojom::CoinType> ToCoinType(
    std::optional<int> val) {
  if (!val) {
    return std::nullopt;
  }
  auto result = static_cast<qorai_wallet::mojom::CoinType>(*val);
  if (!qorai_wallet::mojom::IsKnownEnumValue(result)) {
    return std::nullopt;
  }
  return result;
}

}  // namespace

QoraiWalletHandler::QoraiWalletHandler() = default;
QoraiWalletHandler::~QoraiWalletHandler() = default;

void QoraiWalletHandler::RegisterMessages() {
  web_ui()->RegisterMessageCallback(
      "getAutoLockMinutes",
      base::BindRepeating(&QoraiWalletHandler::GetAutoLockMinutes,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getSolanaProviderOptions",
      base::BindRepeating(&QoraiWalletHandler::GetSolanaProviderOptions,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getCardanoProviderOptions",
      base::BindRepeating(&QoraiWalletHandler::GetCardanoProviderOptions,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getTransactionSimulationOptInStatusOptions",
      base::BindRepeating(
          &QoraiWalletHandler::GetTransactionSimulationOptInStatusOptions,
          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "removeChain", base::BindRepeating(&QoraiWalletHandler::RemoveChain,
                                         base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "resetChain", base::BindRepeating(&QoraiWalletHandler::ResetChain,
                                        base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getNetworksList",
      base::BindRepeating(&QoraiWalletHandler::GetNetworksList,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getPrepopulatedNetworksList",
      base::BindRepeating(&QoraiWalletHandler::GetPrepopulatedNetworksList,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "addChain", base::BindRepeating(&QoraiWalletHandler::AddChain,
                                      base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setDefaultNetwork",
      base::BindRepeating(&QoraiWalletHandler::SetDefaultNetwork,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "addHiddenNetwork",
      base::BindRepeating(&QoraiWalletHandler::AddHiddenNetwork,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "removeHiddenNetwork",
      base::BindRepeating(&QoraiWalletHandler::RemoveHiddenNetwork,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "isBitcoinEnabled",
      base::BindRepeating(&QoraiWalletHandler::IsBitcoinEnabled,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "isZCashEnabled", base::BindRepeating(&QoraiWalletHandler::IsZCashEnabled,
                                            base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "isZCashShieldedTxEnabled",
      base::BindRepeating(&QoraiWalletHandler::IsZCashShieldedTxEnabled,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "isCardanoEnabled",
      base::BindRepeating(&QoraiWalletHandler::IsCardanoEnabled,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "isPolkadotEnabled",
      base::BindRepeating(&QoraiWalletHandler::IsPolkadotEnabled,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "isCardanoDAppSupportEnabled",
      base::BindRepeating(&QoraiWalletHandler::IsCardanoDAppSupportEnabled,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "isTransactionSimulationsFeatureEnabled",
      base::BindRepeating(&QoraiWalletHandler::IsTransactionSimulationsEnabled,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "setWalletInPrivateWindowsEnabled",
      base::BindRepeating(&QoraiWalletHandler::SetWalletInPrivateWindowsEnabled,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getWalletInPrivateWindowsEnabled",
      base::BindRepeating(&QoraiWalletHandler::GetWalletInPrivateWindowsEnabled,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getWeb3ProviderList",
      base::BindRepeating(&QoraiWalletHandler::GetWeb3ProviderList,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "isNativeWalletEnabled",
      base::BindRepeating(&QoraiWalletHandler::IsNativeWalletEnabled,
                          base::Unretained(this)));
}

void QoraiWalletHandler::GetAutoLockMinutes(const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  AllowJavascript();
  ResolveJavascriptCallback(
      args[0],
      base::Value(GetPrefs()->GetInteger(kQoraiWalletAutoLockMinutes)));
}

void QoraiWalletHandler::GetSolanaProviderOptions(
    const base::Value::List& args) {
  base::Value::List list;
  list.Append(MakeSelectValue(
      l10n_util::GetStringUTF16(
          IDS_QORAI_WALLET_WEB3_PROVIDER_QORAI_PREFER_EXTENSIONS),
      ::qorai_wallet::mojom::DefaultWallet::QoraiWalletPreferExtension));
  list.Append(MakeSelectValue(
      l10n_util::GetStringUTF16(IDS_QORAI_WALLET_WEB3_PROVIDER_QORAI),
      ::qorai_wallet::mojom::DefaultWallet::QoraiWallet));
  list.Append(MakeSelectValue(
      l10n_util::GetStringUTF16(IDS_QORAI_WALLET_WEB3_PROVIDER_NONE),
      ::qorai_wallet::mojom::DefaultWallet::None));
  CHECK_EQ(args.size(), 1U);
  AllowJavascript();
  ResolveJavascriptCallback(args[0], list);
}

void QoraiWalletHandler::GetCardanoProviderOptions(
    const base::Value::List& args) {
  base::Value::List list;
  list.Append(MakeSelectValue(
      l10n_util::GetStringUTF16(IDS_QORAI_WALLET_WEB3_PROVIDER_QORAI),
      ::qorai_wallet::mojom::DefaultWallet::QoraiWallet));
  list.Append(MakeSelectValue(
      l10n_util::GetStringUTF16(IDS_QORAI_WALLET_WEB3_PROVIDER_NONE),
      ::qorai_wallet::mojom::DefaultWallet::None));
  CHECK_EQ(args.size(), 1U);
  AllowJavascript();
  ResolveJavascriptCallback(args[0], list);
}

void QoraiWalletHandler::GetTransactionSimulationOptInStatusOptions(
    const base::Value::List& args) {
  base::Value::List list;
  list.Append(
      MakeSelectValue(l10n_util::GetStringUTF16(IDS_SETTINGS_SELECT_VALUE_ASK),
                      ::qorai_wallet::mojom::BlowfishOptInStatus::kUnset));
  list.Append(
      MakeSelectValue(l10n_util::GetStringUTF16(IDS_SETTINGS_SELECT_VALUE_YES),
                      ::qorai_wallet::mojom::BlowfishOptInStatus::kAllowed));
  list.Append(
      MakeSelectValue(l10n_util::GetStringUTF16(IDS_SETTINGS_SELECT_VALUE_NO),
                      ::qorai_wallet::mojom::BlowfishOptInStatus::kDenied));

  CHECK_EQ(args.size(), 1U);
  AllowJavascript();
  ResolveJavascriptCallback(args[0], list);
}

void QoraiWalletHandler::RemoveChain(const base::Value::List& args) {
  CHECK_EQ(args.size(), 3U);
  AllowJavascript();

  auto* chain_id = args[1].GetIfString();
  auto coin = ToCoinType(args[2].GetIfInt());
  if (!chain_id || !coin) {
    ResolveJavascriptCallback(args[0], base::Value());
    return;
  }

  GetNetworkManager()->RemoveCustomNetwork(*chain_id, *coin);
  ResolveJavascriptCallback(args[0], base::Value(true));
}

void QoraiWalletHandler::ResetChain(const base::Value::List& args) {
  CHECK_EQ(args.size(), 3U);
  AllowJavascript();

  auto* chain_id = args[1].GetIfString();
  auto coin = ToCoinType(args[2].GetIfInt());
  if (!chain_id || !coin) {
    ResolveJavascriptCallback(args[0], base::Value());
    return;
  }

  DCHECK(GetNetworkManager()->CustomChainExists(*chain_id, *coin));
  GetNetworkManager()->RemoveCustomNetwork(*chain_id, *coin);
  DCHECK(GetNetworkManager()->KnownChainExists(*chain_id, *coin));
  ResolveJavascriptCallback(args[0], base::Value(true));
}

void QoraiWalletHandler::GetNetworksList(const base::Value::List& args) {
  CHECK_EQ(args.size(), 2U);
  base::Value::Dict result;
  auto coin = ToCoinType(args[1].GetIfInt());
  if (!coin) {
    ResolveJavascriptCallback(args[0], base::Value());
    return;
  }

  result.Set("defaultNetwork",
             GetNetworkManager()->GetCurrentChainId(*coin, std::nullopt));

  auto& networks = result.Set("networks", base::Value::List())->GetList();
  for (const auto& it : GetNetworkManager()->GetAllChains()) {
    if (it->coin == coin) {
      networks.Append(qorai_wallet::NetworkInfoToValue(*it));
    }
  }
  auto& known_networks =
      result.Set("knownNetworks", base::Value::List())->GetList();
  for (const auto& it : GetNetworkManager()->GetAllKnownChains(*coin)) {
    known_networks.Append(it->chain_id);
  }

  auto& custom_networks =
      result.Set("customNetworks", base::Value::List())->GetList();
  for (const auto& it : GetNetworkManager()->GetAllCustomChains(*coin)) {
    custom_networks.Append(it->chain_id);
  }

  auto& hidden_networks =
      result.Set("hiddenNetworks", base::Value::List())->GetList();
  for (const auto& it : GetNetworkManager()->GetHiddenNetworks(*coin)) {
    hidden_networks.Append(it);
  }

  AllowJavascript();
  ResolveJavascriptCallback(args[0], result);
}

void QoraiWalletHandler::GetPrepopulatedNetworksList(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  AllowJavascript();

  base::Value::List networks;

  auto* blockchain_registry = qorai_wallet::BlockchainRegistry::GetInstance();
  if (!blockchain_registry) {
    ResolveJavascriptCallback(args[0], networks);
    return;
  }

  for (const auto& it : blockchain_registry->GetPrepopulatedNetworks()) {
    networks.Append(qorai_wallet::NetworkInfoToValue(*it));
  }

  ResolveJavascriptCallback(args[0], networks);
}

void QoraiWalletHandler::OnAddChain(base::Value javascript_callback,
                                    const std::string& chain_id,
                                    qorai_wallet::mojom::ProviderError error,
                                    const std::string& error_message) {
  base::Value::List result;
  result.Append(error == qorai_wallet::mojom::ProviderError::kSuccess);
  result.Append(error_message);
  ResolveJavascriptCallback(javascript_callback, result);
  if (chain_callback_for_testing_) {
    std::move(chain_callback_for_testing_).Run();
  }
}

void QoraiWalletHandler::AddChain(const base::Value::List& args) {
  CHECK_EQ(args.size(), 2U);
  AllowJavascript();
  auto* qorai_wallet_service =
      qorai_wallet::QoraiWalletServiceFactory::GetServiceForContext(
          Profile::FromWebUI(web_ui()));

  qorai_wallet::mojom::NetworkInfoPtr chain =
      qorai_wallet::ValueToNetworkInfo(args[1]);

  if (!chain || !qorai_wallet_service) {
    base::Value::List result;
    result.Append(false);
    result.Append(l10n_util::GetStringUTF8(
        IDS_SETTINGS_WALLET_NETWORKS_SUMBISSION_FAILED));
    ResolveJavascriptCallback(args[0], result);
    return;
  }

  qorai_wallet_service->json_rpc_service()->AddChain(
      std::move(chain),
      base::BindOnce(&QoraiWalletHandler::OnAddChain,
                     weak_ptr_factory_.GetWeakPtr(), args[0].Clone()));
}

void QoraiWalletHandler::SetDefaultNetwork(const base::Value::List& args) {
  CHECK_EQ(args.size(), 3U);

  auto* chain_id = args[1].GetIfString();
  auto coin = ToCoinType(args[2].GetIfInt());
  if (!chain_id || !coin) {
    ResolveJavascriptCallback(args[0], base::Value());
    return;
  }

  AllowJavascript();
  auto* qorai_wallet_service =
      qorai_wallet::QoraiWalletServiceFactory::GetServiceForContext(
          Profile::FromWebUI(web_ui()));
  auto result = qorai_wallet_service &&
                qorai_wallet_service->json_rpc_service()->SetNetwork(
                    *chain_id, *coin, std::nullopt);
  ResolveJavascriptCallback(args[0], base::Value(result));
}

void QoraiWalletHandler::AddHiddenNetwork(const base::Value::List& args) {
  CHECK_EQ(args.size(), 3U);
  auto* chain_id = args[1].GetIfString();
  auto coin = ToCoinType(args[2].GetIfInt());
  if (!chain_id || !coin) {
    ResolveJavascriptCallback(args[0], base::Value());
    return;
  }

  AllowJavascript();
  GetNetworkManager()->AddHiddenNetwork(*coin, *chain_id);
  ResolveJavascriptCallback(args[0], base::Value(true));
}

void QoraiWalletHandler::RemoveHiddenNetwork(const base::Value::List& args) {
  CHECK_EQ(args.size(), 3U);
  auto* chain_id = args[1].GetIfString();
  auto coin = ToCoinType(args[2].GetIfInt());
  if (!chain_id || !coin) {
    ResolveJavascriptCallback(args[0], base::Value());
    return;
  }

  AllowJavascript();
  GetNetworkManager()->RemoveHiddenNetwork(*coin, *chain_id);
  ResolveJavascriptCallback(args[0], base::Value(true));
}

PrefService* QoraiWalletHandler::GetPrefs() {
  return Profile::FromWebUI(web_ui())->GetPrefs();
}

qorai_wallet::NetworkManager* QoraiWalletHandler::GetNetworkManager() {
  return qorai_wallet::QoraiWalletServiceFactory::GetInstance()
      ->GetServiceForContext(Profile::FromWebUI(web_ui()))
      ->network_manager();
}

void QoraiWalletHandler::IsBitcoinEnabled(const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  AllowJavascript();
  ResolveJavascriptCallback(args[0],
                            base::Value(::qorai_wallet::IsBitcoinEnabled()));
}

void QoraiWalletHandler::IsZCashEnabled(const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  AllowJavascript();
  ResolveJavascriptCallback(args[0],
                            base::Value(::qorai_wallet::IsZCashEnabled()));
}

void QoraiWalletHandler::IsZCashShieldedTxEnabled(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  AllowJavascript();
  ResolveJavascriptCallback(
      args[0],
      base::Value(::qorai_wallet::IsZCashShieldedTransactionsEnabled()));
}

void QoraiWalletHandler::IsCardanoEnabled(const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  AllowJavascript();
  ResolveJavascriptCallback(args[0],
                            base::Value(::qorai_wallet::IsCardanoEnabled()));
}

void QoraiWalletHandler::IsPolkadotEnabled(const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  AllowJavascript();
  ResolveJavascriptCallback(args[0],
                            base::Value(::qorai_wallet::IsPolkadotEnabled()));
}

void QoraiWalletHandler::IsCardanoDAppSupportEnabled(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  AllowJavascript();
  ResolveJavascriptCallback(
      args[0], base::Value(::qorai_wallet::IsCardanoDAppSupportEnabled()));
}

void QoraiWalletHandler::IsTransactionSimulationsEnabled(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  AllowJavascript();
  ResolveJavascriptCallback(
      args[0], base::Value(::qorai_wallet::IsTransactionSimulationsEnabled()));
}

void QoraiWalletHandler::SetWalletInPrivateWindowsEnabled(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 2U);
  bool enabled = args[1].GetBool();
  Profile::FromWebUI(web_ui())->GetPrefs()->SetBoolean(
      kQoraiWalletPrivateWindowsEnabled, enabled);
  AllowJavascript();
  ResolveJavascriptCallback(args[0], base::Value(true));
}

void QoraiWalletHandler::GetWalletInPrivateWindowsEnabled(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  bool enabled = Profile::FromWebUI(web_ui())->GetPrefs()->GetBoolean(
      kQoraiWalletPrivateWindowsEnabled);
  AllowJavascript();
  ResolveJavascriptCallback(args[0], enabled);
}

void QoraiWalletHandler::GetWeb3ProviderList(const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  base::Value::List list;
  list.Append(MakeSelectValue(
      l10n_util::GetStringUTF16(
          IDS_QORAI_WALLET_WEB3_PROVIDER_QORAI_PREFER_EXTENSIONS),
      ::qorai_wallet::mojom::DefaultWallet::QoraiWalletPreferExtension));

  list.Append(MakeSelectValue(
      l10n_util::GetStringUTF16(IDS_QORAI_WALLET_WEB3_PROVIDER_QORAI),
      ::qorai_wallet::mojom::DefaultWallet::QoraiWallet));

  list.Append(MakeSelectValue(
      l10n_util::GetStringUTF16(IDS_QORAI_WALLET_WEB3_PROVIDER_NONE),
      ::qorai_wallet::mojom::DefaultWallet::None));

  std::string json_string;
  base::JSONWriter::Write(list, &json_string);

  AllowJavascript();
  ResolveJavascriptCallback(args[0], base::Value(json_string));
}

void QoraiWalletHandler::IsNativeWalletEnabled(const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  AllowJavascript();
  ResolveJavascriptCallback(
      args[0], base::Value(::qorai_wallet::IsNativeWalletEnabled()));
}
