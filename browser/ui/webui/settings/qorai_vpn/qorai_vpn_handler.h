/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_VPN_QORAI_VPN_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_VPN_QORAI_VPN_HANDLER_H_

#include <string>

#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service_observer.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/webui/settings/settings_page_ui_handler.h"
#include "components/prefs/pref_change_registrar.h"

class QoraiVpnHandler : public settings::SettingsPageUIHandler,
                        public qorai_vpn::QoraiVPNServiceObserver {
 public:
  explicit QoraiVpnHandler(Profile* profile);
  ~QoraiVpnHandler() override;

 private:
  // WebUIMessageHandler implementation.
  void RegisterMessages() override;

  void HandleIsWireguardServiceInstalled(const base::Value::List& args);
  void OnWireguardServiceInstalled(const std::string& callback_id,
                                   bool success);
  void HandleIsQoraiVpnConnected(const base::Value::List& args);

  // qorai_vpn::QoraiVPNServiceObserver
  void OnConnectionStateChanged(
      qorai_vpn::mojom::ConnectionState state) override;
  void OnProtocolChanged();

  // SettingsPageUIHandler implementation.
  void OnJavascriptAllowed() override;
  void OnJavascriptDisallowed() override;

  PrefChangeRegistrar pref_change_registrar_;
  const raw_ptr<Profile, DanglingUntriaged> profile_;
  base::WeakPtrFactory<QoraiVpnHandler> weak_factory_{this};
};

#endif  // QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_VPN_QORAI_VPN_HANDLER_H_
