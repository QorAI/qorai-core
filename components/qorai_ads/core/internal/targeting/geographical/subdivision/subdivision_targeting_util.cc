/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/targeting/geographical/subdivision/subdivision_targeting_util.h"

#include "qorai/components/qorai_ads/core/public/targeting/geographical/subdivision/supported_subdivisions.h"

namespace qorai_ads {

bool ShouldTargetSubdivisionCountryCode(const std::string& country_code) {
  return GetSupportedSubdivisions().contains(country_code);
}

bool ShouldTargetSubdivision(const std::string& country_code,
                             const std::string& subdivision) {
  const SupportedSubdivisionMap& supported_subdivisions =
      GetSupportedSubdivisions();

  const auto iter = supported_subdivisions.find(country_code);
  if (iter == supported_subdivisions.cend()) {
    return false;
  }

  const auto& [_, subdivisions] = *iter;

  return subdivisions.contains(subdivision);
}

}  // namespace qorai_ads
