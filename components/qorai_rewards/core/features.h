/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_FEATURES_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_FEATURES_H_

#include "base/feature_list.h"
#include "qorai/components/qorai_rewards/core/buildflags/buildflags.h"
#include "build/build_config.h"

namespace qorai_rewards::features {

#if BUILDFLAG(IS_ANDROID)
BASE_DECLARE_FEATURE(kQoraiRewards);
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(ENABLE_GEMINI_WALLET)
BASE_DECLARE_FEATURE(kGeminiFeature);
#endif

BASE_DECLARE_FEATURE(kVerboseLoggingFeature);

BASE_DECLARE_FEATURE(kAllowUnsupportedWalletProvidersFeature);

BASE_DECLARE_FEATURE(kAllowSelfCustodyProvidersFeature);

BASE_DECLARE_FEATURE(kAnimatedBackgroundFeature);

BASE_DECLARE_FEATURE(kPlatformCreatorDetectionFeature);

}  // namespace qorai_rewards::features

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_FEATURES_H_
