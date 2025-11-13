/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_VPN_BROWSER_CONNECTION_IKEV2_CONNECTION_API_IMPL_SIM_H_
#define QORAI_COMPONENTS_QORAI_VPN_BROWSER_CONNECTION_IKEV2_CONNECTION_API_IMPL_SIM_H_

#include <optional>
#include <string>

#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_vpn/browser/connection/qorai_vpn_connection_info.h"
#include "qorai/components/qorai_vpn/browser/connection/ikev2/system_vpn_connection_api_impl_base.h"

namespace qorai_vpn {

class ConnectionAPIImplSim : public SystemVPNConnectionAPIImplBase {
 public:
  ConnectionAPIImplSim(
      QoraiVPNConnectionManager* manager,
      scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory);
  ~ConnectionAPIImplSim() override;

  // RasConnectionAPIImpl overrides:
  void Connect() override;
  void Disconnect() override;
  void CheckConnection() override;
  Type type() const override;
  void CreateVPNConnectionImpl(const QoraiVPNConnectionInfo& info) override;
  void ConnectImpl(const std::string& name) override;
  void DisconnectImpl(const std::string& name) override;
  void CheckConnectionImpl(const std::string& name) override;
  bool IsPlatformNetworkAvailable() override;

  bool IsConnectionCreated() const;
  bool IsConnectionChecked() const;
  void SetNetworkAvailableForTesting(bool value);

  void OnCreated(const std::string& name, bool success);
  void OnConnected(const std::string& name, bool success);
  void OnIsConnecting(const std::string& name);
  void OnDisconnected(const std::string& name, bool success);
  void OnIsDisconnecting(const std::string& name);
  void OnRemoved(const std::string& name, bool success);

  bool disconnect_requested_ = false;
  bool connection_created_ = false;
  bool check_connection_called_ = false;

  std::optional<bool> network_available_;
  base::WeakPtrFactory<ConnectionAPIImplSim> weak_factory_{this};
};

}  // namespace qorai_vpn

#endif  // QORAI_COMPONENTS_QORAI_VPN_BROWSER_CONNECTION_IKEV2_CONNECTION_API_IMPL_SIM_H_
