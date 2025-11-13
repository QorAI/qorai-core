/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_USER_MODEL_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_USER_MODEL_INFO_H_

#include "qorai/components/qorai_ads/core/internal/serving/targeting/user_model/intent/intent_user_model_info.h"
#include "qorai/components/qorai_ads/core/internal/serving/targeting/user_model/interest/interest_user_model_info.h"
#include "qorai/components/qorai_ads/core/internal/serving/targeting/user_model/latent_interest/latent_interest_user_model_info.h"

namespace qorai_ads {

struct UserModelInfo final {
  UserModelInfo();
  UserModelInfo(IntentUserModelInfo intent,
                LatentInterestUserModelInfo latent_interest,
                InterestUserModelInfo interest);

  UserModelInfo(const UserModelInfo&);
  UserModelInfo& operator=(const UserModelInfo&);

  UserModelInfo(UserModelInfo&&) noexcept;
  UserModelInfo& operator=(UserModelInfo&&) noexcept;

  ~UserModelInfo();

  bool operator==(const UserModelInfo&) const = default;

  IntentUserModelInfo intent;
  LatentInterestUserModelInfo latent_interest;
  InterestUserModelInfo interest;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_TARGETING_USER_MODEL_USER_MODEL_INFO_H_
