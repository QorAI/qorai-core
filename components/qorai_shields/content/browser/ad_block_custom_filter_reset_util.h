// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_AD_BLOCK_CUSTOM_FILTER_RESET_UTIL_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_AD_BLOCK_CUSTOM_FILTER_RESET_UTIL_H_

#include <optional>
#include <string>

namespace qorai_shields {

std::optional<std::string> ResetCustomFiltersForHost(
    const std::string& host,
    const std::string& custom_filters);

bool IsCustomFiltersAvailable(const std::string& host,
                              const std::string& custom_filters);

}  // namespace qorai_shields

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_CONTENT_BROWSER_AD_BLOCK_CUSTOM_FILTER_RESET_UTIL_H_
