/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/exclusion_rules/marked_as_inappropriate_exclusion_rule.h"

#include "qorai/components/qorai_ads/core/internal/ads_core/ads_core_util.h"
#include "qorai/components/qorai_ads/core/internal/common/logging_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/creative_ad_info.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/reactions/reactions.h"

namespace qorai_ads {

namespace {

bool DoesRespectCap(const CreativeAdInfo& creative_ad) {
  return !GetReactions().IsAdMarkedAsInappropriate(creative_ad.creative_set_id);
}

}  // namespace

std::string MarkedAsInappropriateExclusionRule::GetCacheKey(
    const CreativeAdInfo& creative_ad) const {
  return creative_ad.creative_set_id;
}

bool MarkedAsInappropriateExclusionRule::ShouldInclude(
    const CreativeAdInfo& creative_ad) const {
  if (!DoesRespectCap(creative_ad)) {
    BLOG(1, "creativeSetId "
                << creative_ad.creative_set_id
                << " excluded due to being marked as inappropriate");
    return false;
  }

  return true;
}

}  // namespace qorai_ads
