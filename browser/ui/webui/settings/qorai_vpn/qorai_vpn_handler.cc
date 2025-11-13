/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/settings/qorai_vpn/qorai_vpn_handler.h"

#include <memory>

#include "base/check.h"
#include "base/command_line.h"
#include "base/files/file_path.h"
#include "base/path_service.h"
#include "base/process/launch.h"
#include "base/task/thread_pool.h"
#include "qorai/browser/qorai_vpn/qorai_vpn_service_factory.h"
#include "qorai/browser/qorai_vpn/win/service_constants.h"
#include "qorai/browser/qorai_vpn/win/service_details.h"
#include "qorai/browser/qorai_vpn/win/storage_utils.h"
#include "qorai/browser/qorai_vpn/win/wireguard_utils_win.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#include "qorai/components/qorai_vpn/common/pref_names.h"
#include "chrome/browser/browser_process.h"
#include "components/prefs/pref_service.h"

QoraiVpnHandler::QoraiVpnHandler(Profile* profile) : profile_(profile) {
  auto* service = qorai_vpn::QoraiVpnServiceFactory::GetForProfile(profile);
  CHECK(service);
  Observe(service);

  pref_change_registrar_.Init(g_browser_process->local_state());
  pref_change_registrar_.Add(
      qorai_vpn::prefs::kQoraiVPNWireguardEnabled,
      base::BindRepeating(&QoraiVpnHandler::OnProtocolChanged,
                          base::Unretained(this)));
}

QoraiVpnHandler::~QoraiVpnHandler() = default;

void QoraiVpnHandler::RegisterMessages() {
  web_ui()->RegisterMessageCallback(
      "isWireguardServiceInstalled",
      base::BindRepeating(&QoraiVpnHandler::HandleIsWireguardServiceInstalled,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "isQoraiVpnConnected",
      base::BindRepeating(&QoraiVpnHandler::HandleIsQoraiVpnConnected,
                          base::Unretained(this)));
}

void QoraiVpnHandler::OnProtocolChanged() {
  auto enabled =
      qorai_vpn::IsQoraiVPNWireguardEnabled(g_browser_process->local_state());
  qorai_vpn::SetWireguardActive(enabled);
}

void QoraiVpnHandler::OnWireguardServiceInstalled(
    const std::string& callback_id,
    bool success) {
  AllowJavascript();
  ResolveJavascriptCallback(callback_id, base::Value(success));
}

void QoraiVpnHandler::HandleIsWireguardServiceInstalled(
    const base::Value::List& args) {
  AllowJavascript();

  ResolveJavascriptCallback(
      args[0],
      base::Value(qorai_vpn::wireguard::IsWireguardServiceInstalled()));
}

void QoraiVpnHandler::HandleIsQoraiVpnConnected(const base::Value::List& args) {
  AllowJavascript();

  auto* service = qorai_vpn::QoraiVpnServiceFactory::GetForProfile(profile_);
  ResolveJavascriptCallback(args[0],
                            base::Value(service && service->IsConnected()));
}

void QoraiVpnHandler::OnConnectionStateChanged(
    qorai_vpn::mojom::ConnectionState state) {
  AllowJavascript();
  FireWebUIListener(
      "qorai-vpn-state-change",
      base::Value(state == qorai_vpn::mojom::ConnectionState::CONNECTED));
}

void QoraiVpnHandler::OnJavascriptAllowed() {}

void QoraiVpnHandler::OnJavascriptDisallowed() {}
