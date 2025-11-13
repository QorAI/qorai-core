// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_QORAI_VPN_MAC_VPN_UTILS_MAC_H_
#define QORAI_BROWSER_QORAI_VPN_MAC_VPN_UTILS_MAC_H_

#include <memory>

#include "base/memory/scoped_refptr.h"
#include "qorai/components/qorai_vpn/browser/connection/connection_api_impl.h"

namespace network {
class SharedURLLoaderFactory;
}  // namespace network

namespace qorai_vpn {

class QoraiVPNConnectionManager;

std::unique_ptr<ConnectionAPIImpl> CreateConnectionAPIImplMac(
    QoraiVPNConnectionManager* manager,
    scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory);

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_MAC_VPN_UTILS_MAC_H_
