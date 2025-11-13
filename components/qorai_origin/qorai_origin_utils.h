/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ORIGIN_QORAI_ORIGIN_UTILS_H_
#define QORAI_COMPONENTS_QORAI_ORIGIN_QORAI_ORIGIN_UTILS_H_

#include <optional>
#include <string_view>

namespace qorai_origin {

// Returns whether QoraiOrigin is enabled for the current user.
// This checks the feature flag and will be updated to check actual
// purchase state from SKU service in the future.
bool IsQoraiOriginEnabled();

// Gets the correct qorai_origin_pref_key
std::string GetQoraiOriginPrefKey(std::string_view policy_key,
                                  std::optional<std::string_view> profile_id);

}  // namespace qorai_origin

#endif  // QORAI_COMPONENTS_QORAI_ORIGIN_QORAI_ORIGIN_UTILS_H_
