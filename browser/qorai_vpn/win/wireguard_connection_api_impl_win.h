/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_WIREGUARD_CONNECTION_API_IMPL_WIN_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_WIREGUARD_CONNECTION_API_IMPL_WIN_H_

#include <memory>

#include "base/memory/raw_ptr.h"
#include "base/memory/scoped_refptr.h"
#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_vpn/browser/connection/wireguard/credentials/qorai_vpn_wireguard_profile_credentials.h"
#include "qorai/components/qorai_vpn/common/win/qorai_windows_service_watcher.h"
#include "qorai/components/qorai_vpn/browser/connection/wireguard/wireguard_connection_api_impl_base.h"

namespace qorai_vpn {

class WireguardConnectionAPIImplWin : public WireguardConnectionAPIImplBase {
 public:
  WireguardConnectionAPIImplWin(
      QorAIVPNConnectionManager* manager,
      scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory);
  ~WireguardConnectionAPIImplWin() override;

  // WireguardConnectionAPIImplBase overrides:
  void Disconnect() override;
  void CheckConnection() override;
  void UpdateAndNotifyConnectionStateChange(
      mojom::ConnectionState state) override;
  void PlatformConnectImpl(
      const wireguard::WireguardProfileCredentials& credentials) override;

 private:
  void RunServiceWatcher();
  void OnWireguardServiceLaunched(bool success);
  void OnServiceStopped(int mask);
  void ResetServiceWatcher();

  std::unique_ptr<qorai::ServiceWatcher> service_watcher_;
  base::WeakPtrFactory<WireguardConnectionAPIImplWin> weak_factory_{this};
};

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_WIREGUARD_CONNECTION_API_IMPL_WIN_H_
