/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_rewards/user_rewards_util.h"

#include "qorai/components/qorai_ads/core/internal/account/issuers/issuers_info.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/issuers_util.h"
#include "qorai/components/qorai_ads/core/internal/common/logging_util.h"

namespace qorai_ads {

void UpdateIssuers(const IssuersInfo& issuers) {
  if (!HasIssuersChanged(issuers)) {
    return BLOG(1, "Issuers already up to date");
  }

  BLOG(1, "Updated issuers");
  SetIssuers(issuers);
}

}  // namespace qorai_ads
