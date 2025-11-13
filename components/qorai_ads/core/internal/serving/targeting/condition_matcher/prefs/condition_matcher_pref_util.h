/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_PREFS_CONDITION_MATCHER_PREF_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_PREFS_CONDITION_MATCHER_PREF_UTIL_H_

#include <optional>
#include <string>

#include "base/values.h"

namespace qorai_ads {

// Get the pref value as a string from the provider for the given path. Handles
// nested dictionaries, lists, and dot-separated keys.
// `base::Value::Find*ByDottedPath` is not used because path keys can contain
// dots. Returns `std::nullopt` if the path is malformed or unknown. Path keys
// should be separated by `|`. Example `list|1` would return the second element
// of a list.
std::optional<std::string> MaybeGetPrefValueAsString(
    const base::Value::Dict& virtual_prefs,
    const std::string& pref_path);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_CONDITION_MATCHER_PREFS_CONDITION_MATCHER_PREF_UTIL_H_
