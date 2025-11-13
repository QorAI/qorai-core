/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_WALLET_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_WALLET_HANDLER_H_

#include <string>
#include <utility>

#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_wallet/browser/json_rpc_service.h"
#include "qorai/components/qorai_wallet/browser/network_manager.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "chrome/browser/ui/webui/settings/settings_page_ui_handler.h"

class PrefService;
class Profile;
class TestQoraiWalletHandler;

class QoraiWalletHandler : public settings::SettingsPageUIHandler {
 public:
  QoraiWalletHandler();
  ~QoraiWalletHandler() override;
  QoraiWalletHandler(const QoraiWalletHandler&) = delete;
  QoraiWalletHandler& operator=(const QoraiWalletHandler&) = delete;

  void SetChainCallbackForTesting(base::OnceClosure callback) {
    chain_callback_for_testing_ = std::move(callback);
  }

 private:
  friend TestQoraiWalletHandler;
  // SettingsPageUIHandler overrides:
  void RegisterMessages() override;
  void OnJavascriptAllowed() override {}
  void OnJavascriptDisallowed() override {}

  void GetAutoLockMinutes(const base::Value::List& args);
  void GetSolanaProviderOptions(const base::Value::List& args);
  void GetCardanoProviderOptions(const base::Value::List& args);
  void GetTransactionSimulationOptInStatusOptions(
      const base::Value::List& args);
  void RemoveChain(const base::Value::List& args);
  void ResetChain(const base::Value::List& args);
  void GetNetworksList(const base::Value::List& args);
  void GetPrepopulatedNetworksList(const base::Value::List& args);
  void AddChain(const base::Value::List& args);
  void SetDefaultNetwork(const base::Value::List& args);
  void AddHiddenNetwork(const base::Value::List& args);
  void RemoveHiddenNetwork(const base::Value::List& args);
  void IsBitcoinEnabled(const base::Value::List& args);
  void IsZCashEnabled(const base::Value::List& args);
  void IsZCashShieldedTxEnabled(const base::Value::List& args);
  void IsCardanoEnabled(const base::Value::List& args);
  void IsPolkadotEnabled(const base::Value::List& args);
  void IsCardanoDAppSupportEnabled(const base::Value::List& args);
  void IsTransactionSimulationsEnabled(const base::Value::List& args);
  void SetWalletInPrivateWindowsEnabled(const base::Value::List& args);
  void GetWalletInPrivateWindowsEnabled(const base::Value::List& args);
  void GetWeb3ProviderList(const base::Value::List& args);
  void IsNativeWalletEnabled(const base::Value::List& args);

  PrefService* GetPrefs();
  qorai_wallet::NetworkManager* GetNetworkManager();

  void OnAddChain(base::Value javascript_callback,
                  const std::string& chain_id,
                  qorai_wallet::mojom::ProviderError error,
                  const std::string& error_message);

  base::OnceClosure chain_callback_for_testing_;
  base::WeakPtrFactory<QoraiWalletHandler> weak_ptr_factory_{this};
};

#endif  // QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_WALLET_HANDLER_H_
