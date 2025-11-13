/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_REWARD_REWARD_CONFIRMATION_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_REWARD_REWARD_CONFIRMATION_TEST_UTIL_H_

#include <optional>

namespace qorai_ads {

struct ConfirmationInfo;
struct RewardInfo;

namespace test {

std::optional<ConfirmationInfo> BuildRewardConfirmation(
    bool should_generate_random_uuids);
std::optional<ConfirmationInfo> BuildRewardConfirmationWithoutDynamicUserData(
    bool should_generate_random_uuids);

RewardInfo BuildReward(const ConfirmationInfo& confirmation);

}  // namespace test

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_REWARD_REWARD_CONFIRMATION_TEST_UTIL_H_
