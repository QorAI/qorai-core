/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_URL_URL_UTIL_INTERNAL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_URL_URL_UTIL_INTERNAL_H_

#include <string_view>

class GURL;

namespace qorai_ads {

bool HasSearchQuery(const GURL& url);
bool ShouldSupportInternalUrl(const GURL& url);

bool HostHasRegistryControlledDomain(std::string_view host);

bool DoesETLDPlusOneContainWildcards(const GURL& url);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_URL_URL_UTIL_INTERNAL_H_
