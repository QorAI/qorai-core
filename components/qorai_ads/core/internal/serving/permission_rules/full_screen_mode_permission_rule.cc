/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/full_screen_mode_permission_rule.h"

#include "qorai/components/qorai_ads/core/internal/ads_client/ads_client_util.h"
#include "qorai/components/qorai_ads/core/internal/common/logging_util.h"
#include "qorai/components/qorai_ads/core/internal/common/platform/platform_helper.h"
#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/permission_rule_feature.h"
#include "qorai/components/qorai_ads/core/public/ads_client/ads_client.h"

namespace qorai_ads {

bool HasFullScreenModePermission() {
  if (!kShouldOnlyServeAdsInWindowedMode.Get()) {
    return true;
  }

  if (PlatformHelper::GetInstance().IsMobile()) {
    return true;
  }

  if (!GetAdsClient().IsBrowserInFullScreenMode()) {
    return true;
  }

  BLOG(2, "Full screen mode");
  return false;
}

}  // namespace qorai_ads
