/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/creatives/promoted_content_ads/creative_promoted_content_ads_database_util.h"

#include "base/functional/bind.h"
#include "qorai/components/qorai_ads/core/internal/common/logging_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/promoted_content_ads/creative_promoted_content_ads_database_table.h"

namespace qorai_ads::database {

void SaveCreativePromotedContentAds(
    const CreativePromotedContentAdList& creative_ads) {
  table::CreativePromotedContentAds database_table;
  database_table.Save(
      creative_ads, base::BindOnce([](bool success) {
        if (!success) {
          return BLOG(0, "Failed to save creative promoted content ads");
        }

        BLOG(3, "Successfully saved creative promoted content ads");
      }));
}

}  // namespace qorai_ads::database
