/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/targeting/condition_matcher/prefs/condition_matcher_pref_util.h"

#include "qorai/components/qorai_ads/core/internal/serving/targeting/condition_matcher/prefs/internal/condition_matcher_pref_util_internal.h"

namespace qorai_ads {

std::optional<std::string> MaybeGetPrefValueAsString(
    const base::Value::Dict& virtual_prefs,
    const std::string& pref_path) {
  if (std::optional<base::Value> value =
          MaybeGetPrefValue(virtual_prefs, pref_path)) {
    return ToString(*value);
  }

  // Unknown pref path.
  return std::nullopt;
}

}  // namespace qorai_ads
