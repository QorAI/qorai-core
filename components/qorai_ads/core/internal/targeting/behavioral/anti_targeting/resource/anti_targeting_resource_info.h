/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_ANTI_TARGETING_RESOURCE_ANTI_TARGETING_RESOURCE_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_ANTI_TARGETING_RESOURCE_ANTI_TARGETING_RESOURCE_INFO_H_

#include <map>
#include <optional>
#include <set>
#include <string>

#include "base/values.h"

class GURL;

namespace qorai_ads {

using AntiTargetingSiteList = std::set<GURL>;
using AntiTargetingCreativeSetMap =
    std::map</*creative_set_id*/ std::string, AntiTargetingSiteList>;

struct AntiTargetingResourceInfo final {
  AntiTargetingResourceInfo();

  AntiTargetingResourceInfo(const AntiTargetingResourceInfo&) = delete;
  AntiTargetingResourceInfo& operator=(const AntiTargetingResourceInfo&) =
      delete;

  AntiTargetingResourceInfo(AntiTargetingResourceInfo&&) noexcept;
  AntiTargetingResourceInfo& operator=(AntiTargetingResourceInfo&&) noexcept;

  ~AntiTargetingResourceInfo();

  static std::optional<AntiTargetingResourceInfo> CreateFromValue(
      base::Value::Dict dict);

  std::optional<int> version;
  AntiTargetingCreativeSetMap creative_sets;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_TARGETING_BEHAVIORAL_ANTI_TARGETING_RESOURCE_ANTI_TARGETING_RESOURCE_INFO_H_
