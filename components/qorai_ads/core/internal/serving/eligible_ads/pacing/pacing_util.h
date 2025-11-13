/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PACING_PACING_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PACING_PACING_UTIL_H_

#include <ios>

#include "qorai/components/qorai_ads/core/internal/common/logging_util.h"
#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/pacing/pacing_random_util.h"

namespace qorai_ads {

// Checks if an ad should be paced based on a randomly generated number and the
// ad's pass-through rate. If the random number is less than the pass-through
// rate, the ad is not paced. Otherwise, it is paced.
template <typename T>
bool ShouldPaceAd(const T& ad) {
  const double rand = GeneratePacingRandomNumber();
  if (rand < ad.pass_through_rate) {
    return false;
  }

  BLOG(2, std::fixed << "Pacing delivery for creative instance id "
                     << ad.creative_instance_id << " [Roll("
                     << ad.pass_through_rate << "):" << rand << "]");

  return true;
}

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_PACING_PACING_UTIL_H_
