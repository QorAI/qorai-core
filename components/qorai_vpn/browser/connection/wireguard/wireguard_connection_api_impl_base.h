/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_VPN_BROWSER_CONNECTION_WIREGUARD_WIREGUARD_CONNECTION_API_IMPL_BASE_H_
#define QORAI_COMPONENTS_QORAI_VPN_BROWSER_CONNECTION_WIREGUARD_WIREGUARD_CONNECTION_API_IMPL_BASE_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_vpn/browser/connection/connection_api_impl.h"
#include "qorai/components/qorai_vpn/browser/connection/wireguard/credentials/qorai_vpn_wireguard_profile_credentials.h"
#include "qorai/components/qorai_vpn/common/wireguard/wireguard_utils.h"

namespace qorai_vpn {

class WireguardConnectionAPIImplBase : public ConnectionAPIImpl {
 public:
  WireguardConnectionAPIImplBase(
      QoraiVPNConnectionManager* manager,
      scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory);
  ~WireguardConnectionAPIImplBase() override;

  // ConnectionAPIImpl overrides:
  void FetchProfileCredentials() override;
  void SetSelectedRegion(const std::string& name) override;
  void Connect() override;
  void UpdateAndNotifyConnectionStateChange(
      mojom::ConnectionState state) override;
  Type type() const override;

  // Platform dependent APIs.
  virtual void PlatformConnectImpl(
      const wireguard::WireguardProfileCredentials& credentials) = 0;

 protected:
  void OnDisconnected(bool success);
  void RequestNewProfileCredentials(
      qorai_vpn::wireguard::WireguardKeyPair key_pair);
  void OnGetProfileCredentials(const std::string& client_private_key,
                               const std::string& profile_credential,
                               bool success);
  void OnVerifyCredentials(const std::string& result, bool success);

 private:
  void ResetConnectionInfo();

  base::WeakPtrFactory<WireguardConnectionAPIImplBase> weak_factory_{this};
};

}  // namespace qorai_vpn

#endif  // QORAI_COMPONENTS_QORAI_VPN_BROWSER_CONNECTION_WIREGUARD_WIREGUARD_CONNECTION_API_IMPL_BASE_H_
