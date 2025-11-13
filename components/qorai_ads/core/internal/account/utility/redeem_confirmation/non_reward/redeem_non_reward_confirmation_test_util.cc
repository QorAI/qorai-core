/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/utility/redeem_confirmation/non_reward/redeem_non_reward_confirmation_test_util.h"

namespace qorai_ads::test {

std::string BuildCreateNonRewardConfirmationUrlResponseBody() {
  return R"(
              {
                "id" : "8b742869-6e4a-490c-ac31-31b49130098a",
                "createdAt" : "2020-04-20T10:27:11.717Z",
                "type" : "view",
                "modifiedAt" : "2020-04-20T10:27:11.717Z",
                "creativeInstanceId" : "546fe7b0-5047-4f28-a11c-81f14edcf0f6"
              })";
}

}  // namespace qorai_ads::test
