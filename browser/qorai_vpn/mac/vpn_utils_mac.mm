// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/qorai_vpn/mac/vpn_utils_mac.h"

#include "qorai/components/qorai_vpn/browser/connection/ikev2/mac/ikev2_connection_api_impl_mac.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"

namespace qorai_vpn {

std::unique_ptr<ConnectionAPIImpl> CreateConnectionAPIImplMac(
    QoraiVPNConnectionManager* manager,
    scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory) {
  // NOTE: WIREGUARD is not supported on macOS yet.
  // See https://github.com/qorai/qorai-browser/issues/32612
  return std::make_unique<IKEv2ConnectionAPIImplMac>(manager,
                                                     url_loader_factory);
}

}  // namespace qorai_vpn
