/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_NET_QORAI_REDUCE_LANGUAGE_NETWORK_DELEGATE_HELPER_H_
#define QORAI_BROWSER_NET_QORAI_REDUCE_LANGUAGE_NETWORK_DELEGATE_HELPER_H_

#include <memory>
#include <string>

#include "qorai/browser/net/url_context.h"
#include "url/gurl.h"

class HostContentSettingsMap;
class PrefService;
class Profile;
struct QoraiRequestInfo;

namespace net {
class HttpRequestHeaders;
class URLRequest;
}  // namespace net

namespace qorai {

std::string FarbleAcceptLanguageHeader(
    const GURL& tab_origin,
    Profile* profile,
    HostContentSettingsMap* content_settings);

int OnBeforeStartTransaction_ReduceLanguageWork(
    net::HttpRequestHeaders* headers,
    const ResponseCallback& next_callback,
    std::shared_ptr<QoraiRequestInfo> ctx);

}  // namespace qorai

#endif  // QORAI_BROWSER_NET_QORAI_REDUCE_LANGUAGE_NETWORK_DELEGATE_HELPER_H_
