/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_COMMON_URL_URL_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_COMMON_URL_URL_UTIL_H_

#include <string>
#include <vector>

class GURL;

namespace qorai_ads {

GURL GetUrlExcludingQuery(const GURL& url);

// Returns `true` if the `url` is valid, does not have a port, username, or
// password, is not an IP address, the eTLD+1 does not contain an asterisk
// wildcard, and the host is either on the public suffix list or is a supported
// internal URL.
bool ShouldSupportUrl(const GURL& url);

// Returns `true` if the `url` matches the `pattern`. The pattern string can
// contain asterix wildcards. The backslash character (\) is an escape character
// for *. * matches 0 or more characters.
bool MatchUrlPattern(const GURL& url, const std::string& pattern);
bool MatchUrlPattern(const std::vector<GURL>& redirect_chain,
                     const std::string& pattern);

bool SameDomainOrHost(const GURL&, const GURL&);
bool DomainOrHostExists(const std::vector<GURL>& redirect_chain,
                        const GURL& url);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_COMMON_URL_URL_UTIL_H_
