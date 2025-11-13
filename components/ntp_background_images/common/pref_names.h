// Copyright (c) 2020 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_NTP_BACKGROUND_IMAGES_COMMON_PREF_NAMES_H_
#define QORAI_COMPONENTS_NTP_BACKGROUND_IMAGES_COMMON_PREF_NAMES_H_

namespace ntp_background_images::prefs {

// Survey panelist.
inline constexpr char kNewTabPageSponsoredImagesSurveyPanelist[] =
    "qorai.new_tab_page.sponsored_images.survey_panelist";

// There are two categories in Branded wallpaper.
// The one is sponsored images wallpaper and the other is super referral
// wallpaper.
inline constexpr char kBrandedWallpaperNotificationDismissed[] =
    "qorai.branded_wallpaper_notification_dismissed";
inline constexpr char kNewTabPageShowSponsoredImagesBackgroundImage[] =
    "qorai.new_tab_page.show_branded_background_image";
inline constexpr char kNewTabPageSuperReferralThemesOption[] =
    "qorai.new_tab_page.super_referral_themes_option";
inline constexpr char kNewTabPageShowBackgroundImage[] =
    "qorai.new_tab_page.show_background_image";
inline constexpr char kNewTabTakeoverInfobarRemainingDisplayCount[] =
    "qorai.new_tab_page.new_tab_takeover_infobar_remaining_display_count";

// Local prefs
inline constexpr char kNewTabPageCachedSuperReferralComponentInfo[] =
    "qorai.new_tab_page.cached_super_referral_component_info";
inline constexpr char kNewTabPageCachedSuperReferralComponentData[] =
    "qorai.new_tab_page.cached_super_referral_component_data";
inline constexpr char kNewTabPageGetInitialSuperReferralComponentInProgress[] =
    "qorai.new_tab_page.get_initial_sr_component_in_progress";
inline constexpr char kNewTabPageCachedSuperReferralCode[] =
    "qorai.new_tab_page.cached_referral_code";

}  // namespace ntp_background_images::prefs

#endif  // QORAI_COMPONENTS_NTP_BACKGROUND_IMAGES_COMMON_PREF_NAMES_H_
