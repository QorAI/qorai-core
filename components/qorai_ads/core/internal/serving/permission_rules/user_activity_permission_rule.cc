/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/user_activity_permission_rule.h"

#include "qorai/components/qorai_ads/core/internal/common/logging_util.h"
#include "qorai/components/qorai_ads/core/internal/common/platform/platform_helper.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings.h"
#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_scoring_util.h"

namespace qorai_ads {

bool HasUserActivityPermission() {
  if (!UserHasJoinedQoraiRewardsAndConnectedWallet()) {
    // Allow ads if the user has not joined Qorai Rewards and connected a
    // wallet.
    return true;
  }

  if (PlatformHelper::GetInstance().GetType() == PlatformType::kIOS) {
    return true;
  }

  if (WasUserActive()) {
    return true;
  }

  BLOG(2, "User was inactive");
  return false;
}

}  // namespace qorai_ads
