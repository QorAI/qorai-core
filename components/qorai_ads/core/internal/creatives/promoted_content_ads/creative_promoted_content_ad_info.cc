/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/creatives/promoted_content_ads/creative_promoted_content_ad_info.h"

namespace qorai_ads {

CreativePromotedContentAdInfo::CreativePromotedContentAdInfo() = default;

CreativePromotedContentAdInfo::CreativePromotedContentAdInfo(
    const CreativeAdInfo& creative_ad)
    : CreativeAdInfo(creative_ad) {}

}  // namespace qorai_ads
