/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_NET_QORAI_SYSTEM_REQUEST_HANDLER_H_
#define QORAI_BROWSER_NET_QORAI_SYSTEM_REQUEST_HANDLER_H_

#include <string>

namespace network {
struct ResourceRequest;
}

namespace qorai {

std::string QoraiServicesKeyForTesting();

void AddQoraiServicesKeyHeader(network::ResourceRequest* url_request);

network::ResourceRequest OnBeforeSystemRequest(
    const network::ResourceRequest& url_request);

}  // namespace qorai

#endif  // QORAI_BROWSER_NET_QORAI_SYSTEM_REQUEST_HANDLER_H_
