/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_NET_QORAI_NETWORK_AUDIT_ALLOWED_LISTS_H_
#define QORAI_BROWSER_NET_QORAI_NETWORK_AUDIT_ALLOWED_LISTS_H_

#include <array>
#include <string_view>

#include "base/containers/fixed_flat_set.h"

namespace qorai {

// Before adding to this list, get approval from the security team.
inline constexpr auto kAllowedUrlProtocols =
    base::MakeFixedFlatSet<std::string_view>({
        "chrome-extension",
        "chrome",
        "qorai",
        "file",
        "data",
        "blob",
    });

// Before adding to this list, get approval from the security team.
inline constexpr auto kAllowedUrlPrefixes = std::to_array<std::string_view>({
    // allowed because it 307's to https://componentupdater.qorai.com
    "https://componentupdater.qorai.com/service/update2",
    "https://crxdownload.qorai.com/crx/blobs/",

    // Omaha/Sparkle
    "https://updates.qoraisoftware.com/",

    // stats/referrals
    "https://usage-ping.qorai.com/",

    // needed for DoH on Mac build machines
    "https://dns.google/dns-query",

    // needed for DoH on Mac build machines
    "https://chrome.cloudflare-dns.com/dns-query",

    // for fetching tor client updater component
    "https://tor.qoraisoftware.com/",

    // qorai sync v2 production
    "https://sync-v2.qorai.com/v2",

    // qorai sync v2 staging
    "https://sync-v2.qoraisoftware.com/v2",

    // qorai sync v2 dev
    "https://sync-v2.qorai.software/v2",

    // qorai A/B testing
    "https://variations.qorai.com/seed",

    // Qorai News (production)
    "https://qorai-today-cdn.qorai.com/",

    // Qorai's Privacy-focused CDN
    "https://pcdn.qorai.com/",

    // p3a
    "https://star-randsrv.bsg.qorai.com/",

    // Other
    "https://qorai-core-ext.s3.qorai.com/",
    "https://dict.qorai.com/",
    "https://go-updater.qorai.com/",
    "https://redirector.qorai.com/",
    "https://safebrowsing.qorai.com/",
    "https://static.qorai.com/",
    "https://static1.qorai.com/",
});

}  // namespace qorai

#endif  // QORAI_BROWSER_NET_QORAI_NETWORK_AUDIT_ALLOWED_LISTS_H_
