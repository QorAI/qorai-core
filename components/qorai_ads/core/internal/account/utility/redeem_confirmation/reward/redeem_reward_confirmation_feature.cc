/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_confirmation/reward/redeem_reward_confirmation_feature.h"

namespace qorai_ads {

BASE_FEATURE(kRedeemRewardConfirmationFeature,
             "RedeemRewardConfirmation",
             base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace qorai_ads
