/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_UNSTOPPABLE_DOMAINS_DNS_RESOLVE_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_UNSTOPPABLE_DOMAINS_DNS_RESOLVE_H_

#include <array>
#include <string>

#include "base/containers/span.h"
#include "url/gurl.h"

namespace qorai_wallet::unstoppable_domains {

// See
// https://docs.unstoppabledomains.com/developer-toolkit/resolve-domains-browser/browser-resolution-algorithm/
// for more details.
inline constexpr auto kRecordKeys = std::to_array<std::string_view>({
    "dweb.ipfs.hash",
    "ipfs.html.value",
    "dns.A",
    "dns.AAAA",
    "browser.redirect_url",
    "ipfs.redirect_domain.value",
});

GURL ResolveUrl(base::span<const std::string> response);

}  // namespace qorai_wallet::unstoppable_domains

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_UNSTOPPABLE_DOMAINS_DNS_RESOLVE_H_
