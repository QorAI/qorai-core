/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/issuers_permission_rule.h"

#include "qorai/components/qorai_ads/core/internal/account/issuers/issuers_util.h"
#include "qorai/components/qorai_ads/core/internal/common/logging_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings.h"

namespace qorai_ads {

bool HasIssuersPermission() {
  if (!UserHasJoinedQoraiRewardsAndConnectedWallet()) {
    // Allow ads if the user has not joined Qorai Rewards and connected a
    // wallet, as issuers are not fetched in this case.
    return true;
  }

  if (HasIssuers()) {
    return true;
  }

  BLOG(2, "Missing issuers");
  return false;
}

}  // namespace qorai_ads
