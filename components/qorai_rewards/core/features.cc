/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_rewards/core/features.h"

namespace qorai_rewards::features {

#if BUILDFLAG(IS_ANDROID)
#if defined(ARCH_CPU_X86_FAMILY) && defined(OFFICIAL_BUILD)
BASE_FEATURE(kQoraiRewards, base::FEATURE_DISABLED_BY_DEFAULT);
#else
BASE_FEATURE(kQoraiRewards, base::FEATURE_ENABLED_BY_DEFAULT);
#endif
#endif  // BUILDFLAG(IS_ANDROID)

#if BUILDFLAG(ENABLE_GEMINI_WALLET)
BASE_FEATURE(kGeminiFeature,
             "QoraiRewardsGemini",
             base::FEATURE_ENABLED_BY_DEFAULT);
#endif

BASE_FEATURE(kVerboseLoggingFeature,
             "QoraiRewardsVerboseLogging",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kAllowUnsupportedWalletProvidersFeature,
             "QoraiRewardsAllowUnsupportedWalletProviders",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kAllowSelfCustodyProvidersFeature,
             "QoraiRewardsAllowSelfCustodyProviders",
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kAnimatedBackgroundFeature,
             "QoraiRewardsAnimatedBackground",
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kPlatformCreatorDetectionFeature,
             "QoraiRewardsPlatformCreatorDetection",
#if BUILDFLAG(IS_ANDROID) || BUILDFLAG(IS_IOS)
             base::FEATURE_DISABLED_BY_DEFAULT
#else
             base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

}  // namespace qorai_rewards::features
