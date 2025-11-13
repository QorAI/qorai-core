/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WELCOME_COMMON_FEATURES_H_
#define QORAI_COMPONENTS_QORAI_WELCOME_COMMON_FEATURES_H_

#include "base/feature_list.h"

namespace qorai_welcome {
namespace features {

// If enabled, this will show the Qorai Rewards card in onboarding
BASE_DECLARE_FEATURE(kShowRewardsCard);

}  // namespace features
}  // namespace qorai_welcome

#endif  // QORAI_COMPONENTS_QORAI_WELCOME_COMMON_FEATURES_H_
