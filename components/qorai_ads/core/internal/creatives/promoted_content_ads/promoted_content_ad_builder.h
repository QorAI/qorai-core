/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_PROMOTED_CONTENT_ADS_PROMOTED_CONTENT_AD_BUILDER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_PROMOTED_CONTENT_ADS_PROMOTED_CONTENT_AD_BUILDER_H_

#include <string>

namespace qorai_ads {

struct CreativePromotedContentAdInfo;
struct PromotedContentAdInfo;

PromotedContentAdInfo BuildPromotedContentAd(
    const CreativePromotedContentAdInfo& creative_promoted_content_ad);

PromotedContentAdInfo BuildPromotedContentAd(
    const CreativePromotedContentAdInfo& creative_promoted_content_ad,
    const std::string& placement_id);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_CREATIVES_PROMOTED_CONTENT_ADS_PROMOTED_CONTENT_AD_BUILDER_H_
