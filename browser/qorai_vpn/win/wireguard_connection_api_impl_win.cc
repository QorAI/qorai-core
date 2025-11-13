/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_vpn/win/wireguard_connection_api_impl_win.h"

#include <memory>
#include <string>
#include <tuple>
#include <utility>

#include "base/logging.h"
#include "qorai/browser/qorai_vpn/win/service_details.h"
#include "qorai/browser/qorai_vpn/win/wireguard_utils_win.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_constants.h"
#include "qorai/components/qorai_vpn/common/win/utils.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"

namespace qorai_vpn {

namespace {
// Timer to recheck the service launch after some time.
constexpr int kWireguardServiceRestartTimeoutSec = 5;
}  // namespace

using ConnectionState = mojom::ConnectionState;

WireguardConnectionAPIImplWin::WireguardConnectionAPIImplWin(
      QorAIVPNConnectionManager* manager,
      scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory)
    : WireguardConnectionAPIImplBase(manager, url_loader_factory) {}

WireguardConnectionAPIImplWin::~WireguardConnectionAPIImplWin() = default;

void WireguardConnectionAPIImplWin::Disconnect() {
  if (GetConnectionState() == ConnectionState::DISCONNECTED) {
    VLOG(2) << __func__ << " : already disconnected";
    return;
  }
  VLOG(2) << __func__ << " : Start stopping the service";
  UpdateAndNotifyConnectionStateChange(ConnectionState::DISCONNECTING);

  qorai_vpn::wireguard::DisableQorAIVpnWireguardService(
      base::BindOnce(&WireguardConnectionAPIImplWin::OnDisconnected,
                                weak_factory_.GetWeakPtr()));
}

void WireguardConnectionAPIImplWin::CheckConnection() {
  auto state = IsWindowsServiceRunning(
                   qorai_vpn::GetQorAIVpnWireguardTunnelServiceName())
                   ? ConnectionState::CONNECTED
                   : ConnectionState::DISCONNECTED;
  UpdateAndNotifyConnectionStateChange(state);
}

void WireguardConnectionAPIImplWin::PlatformConnectImpl(
    const wireguard::WireguardProfileCredentials& credentials) {
  auto vpn_server_hostname = GetHostname();
  std::optional<std::string> smart_proxy_url;
  if (SmartRoutingEnabled()) {
    smart_proxy_url = kProxyUrl;
  }
  qorai_vpn::wireguard::EnableQorAIVpnWireguardService(
      credentials.server_public_key, credentials.client_private_key,
      credentials.mapped_ip4_address, vpn_server_hostname,
      std::move(smart_proxy_url),
      base::BindOnce(&WireguardConnectionAPIImplWin::OnWireguardServiceLaunched,
                     weak_factory_.GetWeakPtr()));
}

void WireguardConnectionAPIImplWin::OnServiceStopped(int mask) {
  // Postpone check because the service can be restarted by the system due to
  // configured failure actions.
  base::SequencedTaskRunner::GetCurrentDefault()->PostDelayedTask(
      FROM_HERE,
      base::BindOnce(&WireguardConnectionAPIImplWin::CheckConnection,
                     weak_factory_.GetWeakPtr()),
      base::Seconds(kWireguardServiceRestartTimeoutSec));
  ResetServiceWatcher();
}

void WireguardConnectionAPIImplWin::RunServiceWatcher() {
  if (service_watcher_ && service_watcher_->IsWatching()) {
    return;
  }
  service_watcher_.reset(new qorai::ServiceWatcher());
  if (!service_watcher_->Subscribe(
          qorai_vpn::GetQorAIVpnWireguardTunnelServiceName(),
          SERVICE_NOTIFY_STOPPED,
          base::BindRepeating(
              &WireguardConnectionAPIImplWin::OnServiceStopped,
              weak_factory_.GetWeakPtr()))) {
    VLOG(1) << "Unable to set service watcher";
  }
}

void WireguardConnectionAPIImplWin::ResetServiceWatcher() {
  if (service_watcher_) {
    service_watcher_.reset();
  }
}

void WireguardConnectionAPIImplWin::OnWireguardServiceLaunched(
    bool success) {
  UpdateAndNotifyConnectionStateChange(
      success ? ConnectionState::CONNECTED : ConnectionState::CONNECT_FAILED);
}

void WireguardConnectionAPIImplWin::UpdateAndNotifyConnectionStateChange(
    mojom::ConnectionState state) {
  WireguardConnectionAPIImplBase::UpdateAndNotifyConnectionStateChange(state);
  if (state == ConnectionState::CONNECTED) {
    RunServiceWatcher();
    return;
  }
  ResetServiceWatcher();
}

}  // namespace qorai_vpn
