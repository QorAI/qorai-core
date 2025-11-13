// Copyright (c) 2020 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_shields/core/common/features.h"

#include "base/feature_list.h"

namespace qorai_shields::features {

BASE_FEATURE(kAdBlockDefaultResourceUpdateInterval,
             base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, Qorai will block first-party requests that appear in a filter
// list when Shields is in "standard" blocking mode. When disabled, Qorai will
// allow first-party requests in "standard" blocking mode regardless of whether
// or not they appear in a filter list.
BASE_FEATURE(kQoraiAdblockDefault1pBlocking,
             base::FEATURE_DISABLED_BY_DEFAULT);
// When enabled, Qorai will issue DNS queries for requests that the adblock
// engine has not blocked, then check them again with the original hostname
// substituted for any canonical name found.
BASE_FEATURE(kQoraiAdblockCnameUncloaking,
             base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, Qorai will apply HTML element collapsing to all images and
// iframes that initiate a blocked network request.
BASE_FEATURE(kQoraiAdblockCollapseBlockedElements,
             base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, Qorai will enable "Easylist-Cookie List" by default unless
// overridden by a locally set preference.
BASE_FEATURE(kQoraiAdblockCookieListDefault,
             base::FEATURE_ENABLED_BY_DEFAULT);
BASE_FEATURE(kQoraiAdblockCosmeticFiltering,
             base::FEATURE_ENABLED_BY_DEFAULT);
// Qorai will apply cosmetic filters with procedural operators like
// `:has-text(...)` and `:upward(...)`.
BASE_FEATURE(kQoraiAdblockProceduralFiltering,
             base::FEATURE_ENABLED_BY_DEFAULT);
BASE_FEATURE(kQoraiAdblockScriptletDebugLogs,
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kQoraiAdblockCspRules,
             base::FEATURE_ENABLED_BY_DEFAULT);
BASE_FEATURE(kQoraiAdblockShowHiddenComponents,
             base::FEATURE_DISABLED_BY_DEFAULT);
// When enabled, Qorai will enable "Fanboy's Mobile Notifications List" by
// default unless overridden by a locally set preference.
BASE_FEATURE(kQoraiAdblockMobileNotificationsListDefault,
             base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, Qorai will enable "Qorai Experimental Adblock Rules" list by
// default unless overridden by a locally set preference.
// NOTE: this should only be turned on by default in Nightly and Beta.
BASE_FEATURE(kQoraiAdblockExperimentalListDefault,
             base::FEATURE_DISABLED_BY_DEFAULT);
// When enabled, Qorai will block domains listed in the user's selected adblock
// filters and present a security interstitial with choice to proceed and
// optionally whitelist the domain.
// Domain block filters look like this:
// ||ads.example.com^
BASE_FEATURE(kQoraiDomainBlock,
             base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, Qorai will attempt to enable 1PES mode in a standard blocking
// mode when a user visists a domain that is present in currently active adblock
// filters. 1PES will be enabled only if neither cookies nor localStorage data
// is stored for the website.
BASE_FEATURE(kQoraiDomainBlock1PES,
             base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, network requests initiated by extensions will be checked and
// potentially blocked by Qorai Shields.
BASE_FEATURE(kQoraiExtensionNetworkBlocking,
             base::FEATURE_DISABLED_BY_DEFAULT);
// Enables Qorai farbling (randomization of fingerprinting-susceptible WebAPIs).
BASE_FEATURE(kQoraiFarbling, base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, language headers and APIs may be altered by Qorai Shields.
BASE_FEATURE(kQoraiReduceLanguage,
             base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, qorai shred feature will be available
BASE_FEATURE(kQoraiShredFeature,
#if BUILDFLAG(IS_IOS)
             base::FEATURE_ENABLED_BY_DEFAULT);
#else
             base::FEATURE_DISABLED_BY_DEFAULT);
#endif
// When enabled, qorai shred will clear all cache data when shredding.
BASE_FEATURE(kQoraiShredCacheData,
#if BUILDFLAG(IS_IOS)
             base::FEATURE_ENABLED_BY_DEFAULT);
#else
             base::FEATURE_DISABLED_BY_DEFAULT);
#endif
// When enabled, qorai will use content settings for Shields on iOS.
BASE_FEATURE(kQoraiShieldsContentSettingsIOS,
             base::FEATURE_DISABLED_BY_DEFAULT);
// When enabled, will display debug menu for adblock features in the Shields
// panel.
BASE_FEATURE(kQoraiIOSDebugAdblock,
             base::FEATURE_DISABLED_BY_DEFAULT);
// When enabled, will farble navigator.plugins.
BASE_FEATURE(kQoraiIOSEnableFarblingPlugins,
             base::FEATURE_ENABLED_BY_DEFAULT);
// When enabled, show Strict (aggressive) fingerprinting mode in Qorai Shields.
BASE_FEATURE(kQoraiShowStrictFingerprintingMode,
             base::FEATURE_DISABLED_BY_DEFAULT);
// when enabled, qorai will prompt for permission on sites which want to connect
// to localhost.
BASE_FEATURE(kQoraiLocalhostAccessPermission,
             base::FEATURE_DISABLED_BY_DEFAULT);
// When enabled, Qorai will always report Light in Fingerprinting: Strict mode
BASE_FEATURE(kQoraiDarkModeBlock,
             base::FEATURE_ENABLED_BY_DEFAULT);
// load the cosmetic filter rules using sync ipc
BASE_FEATURE(kCosmeticFilteringSyncLoad,
             "CosmeticFilterSyncLoad",
             base::FEATURE_ENABLED_BY_DEFAULT);
// If the feature flag is on, we show the Block all Cookies toggle
BASE_FEATURE(kBlockAllCookiesToggle,
#if BUILDFLAG(IS_IOS)
             base::FEATURE_ENABLED_BY_DEFAULT);
#else
             base::FEATURE_DISABLED_BY_DEFAULT);
#endif
// when enabled, allow to select and block HTML elements
BASE_FEATURE(kQoraiShieldsElementPicker,
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kAdblockOnlyMode,
             base::FEATURE_DISABLED_BY_DEFAULT);

// Enables extra TRACE_EVENTs in content filter js. The feature is
// primary designed for local debugging.
BASE_FEATURE(kCosmeticFilteringExtraPerfMetrics,
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kCosmeticFilteringJsPerformance,
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kCosmeticFilteringCustomScriptlets,
             base::FEATURE_ENABLED_BY_DEFAULT);

BASE_FEATURE(kWebKitAdvancedPrivacyProtections,
             base::FEATURE_DISABLED_BY_DEFAULT);

constexpr base::FeatureParam<int> kComponentUpdateCheckIntervalMins{
    &kAdBlockDefaultResourceUpdateInterval, "update_interval_mins", 100};

constexpr base::FeatureParam<std::string>
    kCosmeticFilteringSubFrameFirstSelectorsPollingDelayMs{
        &kCosmeticFilteringJsPerformance, "subframes_first_query_delay_ms",
        "1000"};

constexpr base::FeatureParam<std::string>
    kCosmeticFilteringswitchToSelectorsPollingThreshold{
        &kCosmeticFilteringJsPerformance, "switch_to_polling_threshold",
        "1000"};

constexpr base::FeatureParam<std::string>
    kCosmeticFilteringFetchNewClassIdRulesThrottlingMs{
        &kCosmeticFilteringJsPerformance, "fetch_throttling_ms", "100"};

BASE_FEATURE(kAdblockOverrideRegexDiscardPolicy,
             base::FEATURE_DISABLED_BY_DEFAULT);

constexpr base::FeatureParam<int>
    kAdblockOverrideRegexDiscardPolicyCleanupIntervalSec{
        &kAdblockOverrideRegexDiscardPolicy, "cleanup_interval_sec", 0};

constexpr base::FeatureParam<int>
    kAdblockOverrideRegexDiscardPolicyDiscardUnusedSec{
        &kAdblockOverrideRegexDiscardPolicy, "discard_unused_sec", 180};

}  // namespace qorai_shields::features
