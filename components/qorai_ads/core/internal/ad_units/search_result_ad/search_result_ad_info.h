/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_AD_UNITS_SEARCH_RESULT_AD_SEARCH_RESULT_AD_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_AD_UNITS_SEARCH_RESULT_AD_SEARCH_RESULT_AD_INFO_H_

#include <string>

#include "qorai/components/qorai_ads/core/public/ad_units/ad_info.h"

namespace qorai_ads {

struct SearchResultAdInfo final : AdInfo {
  [[nodiscard]] bool IsValid() const;

  std::string headline_text;
  std::string description;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_AD_UNITS_SEARCH_RESULT_AD_SEARCH_RESULT_AD_INFO_H_
