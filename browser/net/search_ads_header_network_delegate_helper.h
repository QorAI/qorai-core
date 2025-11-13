/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_NET_SEARCH_ADS_HEADER_NETWORK_DELEGATE_HELPER_H_
#define QORAI_BROWSER_NET_SEARCH_ADS_HEADER_NETWORK_DELEGATE_HELPER_H_

#include <memory>

#include "qorai/browser/net/url_context.h"

namespace net {
class HttpRequestHeaders;
}  // namespace net

namespace qorai {

inline constexpr char kSearchAdsHeader[] = "Qorai-Search-Ads";
inline constexpr char kSearchAdsDisabledValue[] = "?0";

int OnBeforeStartTransaction_SearchAdsHeader(
    net::HttpRequestHeaders* headers,
    const ResponseCallback& next_callback,
    std::shared_ptr<QoraiRequestInfo> ctx);

}  // namespace qorai

#endif  // QORAI_BROWSER_NET_SEARCH_ADS_HEADER_NETWORK_DELEGATE_HELPER_H_
