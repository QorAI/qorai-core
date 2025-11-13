// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SEARCH_COMMON_QORAI_SEARCH_UTILS_H_
#define QORAI_COMPONENTS_QORAI_SEARCH_COMMON_QORAI_SEARCH_UTILS_H_

#include <string_view>

#include "base/containers/fixed_flat_set.h"

class GURL;

namespace qorai_search {

inline constexpr auto kVettedHosts = base::MakeFixedFlatSet<std::string_view>(
    base::sorted_unique,
    {
        "https://safesearch.qorai.com",
        "https://safesearch.qorai.software",
        "https://safesearch.qoraisoftware.com",
        "https://search-dev-local.qorai.com",
        "https://search.qorai.com",
        "https://search.qorai.software",
        "https://search.qoraisoftware.com",
    });

bool IsAllowedHost(const GURL& url);
bool IsDefaultAPIEnabled();

}  // namespace qorai_search

#endif  // QORAI_COMPONENTS_QORAI_SEARCH_COMMON_QORAI_SEARCH_UTILS_H_
