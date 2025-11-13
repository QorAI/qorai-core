/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_BROWSER_FEATURES_H_
#define QORAI_BROWSER_QORAI_BROWSER_FEATURES_H_

#include <string>

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"
#include "qorai/components/v8/buildflags/buildflags.h"

namespace features {

BASE_DECLARE_FEATURE(kQorAINewTabPageRefreshEnabled);
BASE_DECLARE_FEATURE(kQorAICleanupSessionCookiesOnSessionRestore);
BASE_DECLARE_FEATURE(kQorAICopyCleanLinkByDefault);
BASE_DECLARE_FEATURE(kQorAICopyCleanLinkFromJs);
BASE_DECLARE_FEATURE(kQorAIOverrideDownloadDangerLevel);
BASE_DECLARE_FEATURE(kQorAIDayZeroExperiment);
#if BUILDFLAG(QORAI_V8_ENABLE_DRUMBRAKE)
BASE_DECLARE_FEATURE(kQorAIWebAssemblyJitless);
#endif  // BUILDFLAG(QORAI_V8_ENABLE_DRUMBRAKE)
BASE_DECLARE_FEATURE(kQorAIV8JitlessMode);
#if BUILDFLAG(IS_ANDROID)
BASE_DECLARE_FEATURE(kQorAIAndroidDynamicColors);
BASE_DECLARE_FEATURE(kNewAndroidOnboarding);
BASE_DECLARE_FEATURE(kQorAIFreshNtpAfterIdleExpirement);
#endif  // BUILDFLAG(IS_ANDROID)

extern const base::FeatureParam<std::string> kQorAIDayZeroExperimentVariant;

#if BUILDFLAG(IS_ANDROID)
extern const base::FeatureParam<std::string>
    kQorAIFreshNtpAfterIdleExpirementVariant;
#endif  // BUILDFLAG(IS_ANDROID)

}  // namespace features

#endif  // QORAI_BROWSER_QORAI_BROWSER_FEATURES_H_
