/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_PREFS_PREF_NAMES_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_PREFS_PREF_NAMES_H_

namespace qorai_ads::prefs {

// IMPORTANT: Prefs that need clearing should be prefixed with
// `qorai.qorai_ads`.

// Ads prefs.
inline constexpr char kFirstRunAt[] = "qorai.qorai_ads.first_run_at";

inline constexpr char kGracePeriod[] = "qorai.qorai_ads.grace_period";

inline constexpr char kDiagnosticId[] = "qorai.qorai_ads.diagnostics.id";

inline constexpr char kOptedInToNotificationAds[] = "qorai.qorai_ads.enabled";
inline constexpr char kMaximumNotificationAdsPerHour[] =
    "qorai.qorai_ads.ads_per_hour";

inline constexpr char kOptedInToSearchResultAds[] =
    "qorai.qorai_ads.opted_in_to_search_result_ads";

inline constexpr char kShouldAllowSubdivisionTargeting[] =
    "qorai.qorai_ads.should_allow_ads_subdivision_targeting";
inline constexpr char kSubdivisionTargetingUserSelectedSubdivision[] =
    "qorai.qorai_ads.ads_subdivision_targeting_code";
inline constexpr char kSubdivisionTargetingAutoDetectedSubdivision[] =
    "qorai.qorai_ads.automatically_detected_ads_subdivision_targeting_code";

inline constexpr char kCatalogId[] = "qorai.qorai_ads.catalog_id";
inline constexpr char kCatalogVersion[] = "qorai.qorai_ads.catalog_version";
inline constexpr char kCatalogPing[] = "qorai.qorai_ads.catalog_ping";
inline constexpr char kCatalogLastUpdated[] =
    "qorai.qorai_ads.catalog_last_updated";

inline constexpr char kIssuerPing[] = "qorai.qorai_ads.issuer_ping";
inline constexpr char kIssuers[] = "qorai.qorai_ads.issuers";

inline constexpr char kNotificationAds[] = "qorai.qorai_ads.notification_ads";
inline constexpr char kServeAdAt[] = "qorai.qorai_ads.serve_ad_at";

inline constexpr char kNextPaymentTokenRedemptionAt[] =
    "qorai.qorai_ads.rewards.next_time_redemption_at";

inline constexpr char kAdReactions[] = "qorai.qorai_ads.reactions.ads";
inline constexpr char kSegmentReactions[] =
    "qorai.qorai_ads.reactions.segments";
inline constexpr char kSaveAds[] = "qorai.qorai_ads.reactions.saved_ads";
inline constexpr char kMarkedAsInappropriate[] =
    "qorai.qorai_ads.reactions.marked_as_inappropriate";

inline constexpr char kHasMigratedState[] =
    "qorai.qorai_ads.state.has_migrated.v2";
inline constexpr char kHasMigratedClientState[] =
    "qorai.qorai_ads.state.has_migrated.client.v7";
inline constexpr char kHasMigratedConfirmationState[] =
    "qorai.qorai_ads.state.has_migrated.confirmations.v8";

inline constexpr char kBrowserVersionNumber[] =
    "qorai.qorai_ads.browser_version_number";

// Ads service prefs.
inline constexpr char kNotificationAdLastNormalizedCoordinateX[] =
    "qorai.qorai_ads.ad_notification.last_normalized_coordinate_x";
inline constexpr char kNotificationAdLastNormalizedCoordinateY[] =
    "qorai.qorai_ads.ad_notification.last_normalized_coordinate_y";
inline constexpr char kNotificationAdDidFallbackToCustom[] =
    "qorai.qorai_ads.ad_notification.did_fallback_to_custom";

inline constexpr char kShouldShowOnboardingNotification[] =
    "qorai.qorai_ads.should_show_my_first_ad_notification";

// Qorai stats prefs.
inline constexpr char kEnabledForLastProfile[] =
    "qorai.qorai_ads.enabled_last_profile";
inline constexpr char kEverEnabledForAnyProfile[] =
    "qorai.qorai_ads.ever_enabled_any_profile";

// We don't prefix `qorai.qorai_ads` to this pref path because we don't want
// them cleared if the user clears ads data or resets Qorai Rewards.
inline constexpr char kShouldShowSearchResultAdClickedInfoBar[] =
    "qorai.search.search_result_ad.should_show_clicked_infobar";

}  // namespace qorai_ads::prefs

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_PREFS_PREF_NAMES_H_
