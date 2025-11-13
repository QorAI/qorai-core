/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_VPN_UTILS_H_
#define QORAI_BROWSER_QORAI_VPN_VPN_UTILS_H_

#include <memory>

#include "base/memory/scoped_refptr.h"

namespace content {
class BrowserContext;
}  // namespace content

namespace network {
class SharedURLLoaderFactory;
}  // namespace network

class PrefService;

namespace qorai_vpn {

class QoraiVPNConnectionManager;

bool IsQoraiVPNEnabled(content::BrowserContext* context);
bool IsAllowedForContext(content::BrowserContext* context);
std::unique_ptr<QoraiVPNConnectionManager> CreateQoraiVPNConnectionManager(
    scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory,
    PrefService* local_prefs);

}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_VPN_UTILS_H_
