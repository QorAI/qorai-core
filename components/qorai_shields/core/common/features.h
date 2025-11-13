// Copyright (c) 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_CORE_COMMON_FEATURES_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_CORE_COMMON_FEATURES_H_

#include <cstddef>
#include <string>

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"
#include "base/time/time.h"

namespace qorai_shields {
namespace features {
BASE_DECLARE_FEATURE(kAdBlockDefaultResourceUpdateInterval);
BASE_DECLARE_FEATURE(kQoraiAdblockCnameUncloaking);
BASE_DECLARE_FEATURE(kQoraiAdblockCollapseBlockedElements);
BASE_DECLARE_FEATURE(kQoraiAdblockCookieListDefault);
BASE_DECLARE_FEATURE(kQoraiAdblockCosmeticFiltering);
BASE_DECLARE_FEATURE(kQoraiAdblockProceduralFiltering);
BASE_DECLARE_FEATURE(kQoraiAdblockCspRules);
BASE_DECLARE_FEATURE(kQoraiAdblockDefault1pBlocking);
BASE_DECLARE_FEATURE(kQoraiAdblockMobileNotificationsListDefault);
BASE_DECLARE_FEATURE(kQoraiAdblockExperimentalListDefault);
BASE_DECLARE_FEATURE(kQoraiAdblockScriptletDebugLogs);
BASE_DECLARE_FEATURE(kQoraiAdblockShowHiddenComponents);
BASE_DECLARE_FEATURE(kQoraiDarkModeBlock);
BASE_DECLARE_FEATURE(kQoraiDomainBlock);
BASE_DECLARE_FEATURE(kQoraiDomainBlock1PES);
BASE_DECLARE_FEATURE(kQoraiExtensionNetworkBlocking);
BASE_DECLARE_FEATURE(kQoraiFarbling);
BASE_DECLARE_FEATURE(kQoraiLocalhostAccessPermission);
BASE_DECLARE_FEATURE(kQoraiReduceLanguage);
BASE_DECLARE_FEATURE(kQoraiShredFeature);
BASE_DECLARE_FEATURE(kQoraiShredCacheData);
BASE_DECLARE_FEATURE(kQoraiShieldsContentSettingsIOS);
BASE_DECLARE_FEATURE(kQoraiIOSDebugAdblock);
BASE_DECLARE_FEATURE(kQoraiIOSEnableFarblingPlugins);
BASE_DECLARE_FEATURE(kQoraiShowStrictFingerprintingMode);
BASE_DECLARE_FEATURE(kCosmeticFilteringExtraPerfMetrics);
BASE_DECLARE_FEATURE(kCosmeticFilteringJsPerformance);
BASE_DECLARE_FEATURE(kCosmeticFilteringSyncLoad);
BASE_DECLARE_FEATURE(kBlockAllCookiesToggle);
BASE_DECLARE_FEATURE(kCosmeticFilteringCustomScriptlets);
BASE_DECLARE_FEATURE(kQoraiShieldsElementPicker);
BASE_DECLARE_FEATURE(kWebKitAdvancedPrivacyProtections);
extern const base::FeatureParam<int> kComponentUpdateCheckIntervalMins;
extern const base::FeatureParam<std::string>
    kCosmeticFilteringSubFrameFirstSelectorsPollingDelayMs;
extern const base::FeatureParam<std::string>
    kCosmeticFilteringswitchToSelectorsPollingThreshold;
extern const base::FeatureParam<std::string>
    kCosmeticFilteringFetchNewClassIdRulesThrottlingMs;
BASE_DECLARE_FEATURE(kAdblockOverrideRegexDiscardPolicy);
extern const base::FeatureParam<int>
    kAdblockOverrideRegexDiscardPolicyCleanupIntervalSec;
extern const base::FeatureParam<int>
    kAdblockOverrideRegexDiscardPolicyDiscardUnusedSec;

BASE_DECLARE_FEATURE(kAdblockOnlyMode);
// The number of times the shields are disabled before showing the Ad Block Only
// mode prompt in Shields Panel.
inline constexpr base::FeatureParam<int>
    kAdblockOnlyModePromptAfterShieldsDisabledCount{
        &kAdblockOnlyMode, "prompt_after_shields_disabled_count", 5};
// The time interval after which the Ad Block Only mode repeated reloads prompt
// is shown.
inline constexpr base::FeatureParam<base::TimeDelta>
    kAdblockOnlyModePromptAfterPageReloadsInterval{
        &kAdblockOnlyMode, "prompt_after_page_reloads_interval",
        base::Seconds(10)};
// The minimum number of times the page is reloaded before showing the Ad Block
// Only mode repeated reloads prompt.
inline constexpr base::FeatureParam<size_t>
    kAdblockOnlyModePromptAfterPageReloadsMin{
        &kAdblockOnlyMode, "prompt_after_page_reloads_min", 0};
// The maximum number of times the page is reloaded before showing the Ad Block
// Only mode repeated reloads prompt.
inline constexpr base::FeatureParam<size_t>
    kAdblockOnlyModePromptAfterPageReloadsMax{
        &kAdblockOnlyMode, "prompt_after_page_reloads_max", 0};

}  // namespace features
}  // namespace qorai_shields

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_CORE_COMMON_FEATURES_H_
