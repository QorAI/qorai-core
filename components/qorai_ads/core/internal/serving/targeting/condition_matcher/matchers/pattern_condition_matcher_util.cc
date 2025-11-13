/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/targeting/condition_matcher/matchers/pattern_condition_matcher_util.h"

#include "base/strings/pattern.h"

namespace qorai_ads {

bool MatchPattern(std::string_view value, std::string_view condition) {
  return base::MatchPattern(value, condition);
}

}  // namespace qorai_ads
