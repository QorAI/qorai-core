/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_REWARDS_REWARDS_UTIL_H_
#define QORAI_BROWSER_QORAI_REWARDS_REWARDS_UTIL_H_

#include "qorai/components/qorai_rewards/core/rewards_util.h"

class Profile;

namespace qorai_rewards {

bool IsSupportedForProfile(
    Profile* profile,
    IsSupportedOptions options = IsSupportedOptions::kNone);

}  // namespace qorai_rewards

#endif  // QORAI_BROWSER_QORAI_REWARDS_REWARDS_UTIL_H_
