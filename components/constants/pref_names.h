/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_CONSTANTS_PREF_NAMES_H_
#define QORAI_COMPONENTS_CONSTANTS_PREF_NAMES_H_

#include "qorai/components/web_discovery/buildflags/buildflags.h"
#include "build/build_config.h"
#include "extensions/buildflags/buildflags.h"

inline constexpr char kQoraiAutofillPrivateWindows[] =
    "qorai.autofill_private_windows";
inline constexpr char kManagedQoraiShieldsDisabledForUrls[] =
    "qorai.managed_shields_disabled";
inline constexpr char kManagedQoraiShieldsEnabledForUrls[] =
    "qorai.managed_shields_enabled";
inline constexpr char kManagedDefaultQoraiFingerprintingV2[] =
    "qorai.profile.managed_default_content_settings.qorai_fingerprinting_v2";
inline constexpr char kAdsBlocked[] = "qorai.stats.ads_blocked";
// We no longer update this pref, but we keep it around for now because it's
// added to kAdsBlocked when being displayed.
inline constexpr char kTrackersBlocked[] = "qorai.stats.trackers_blocked";
inline constexpr char kJavascriptBlocked[] = "qorai.stats.javascript_blocked";
inline constexpr char kHttpsUpgrades[] = "qorai.stats.https_upgrades";
inline constexpr char kFingerprintingBlocked[] =
    "qorai.stats.fingerprinting_blocked";
inline constexpr char kLastCheckYMD[] = "qorai.stats.last_check_ymd";
inline constexpr char kLastCheckWOY[] = "qorai.stats.last_check_woy";
inline constexpr char kLastCheckMonth[] = "qorai.stats.last_check_month";
inline constexpr char kFirstCheckMade[] = "qorai.stats.first_check_made";
// Set to true if the user met the threshold requirements and successfully
// sent a ping to the stats-updater server.
inline constexpr char kThresholdCheckMade[] =
    "qorai.stats.threshold_check_made";
// Anonymous usage pings enabled
inline constexpr char kStatsReportingEnabled[] =
    "qorai.stats.reporting_enabled";
// Serialized query for to send to the stats-updater server. Needs to be saved
// in the case that the user sends the standard usage ping, stops the browser,
// meets the threshold requirements, and then starts the browser before the
// threshold ping was sent.
inline constexpr char kThresholdQuery[] = "qorai.stats.threshold_query";
inline constexpr char kWeekOfInstallation[] =
    "qorai.stats.week_of_installation";
inline constexpr char kWidevineEnabled[] = "qorai.widevine_opted_in";
inline constexpr char kAskEnableWidvine[] = "qorai.ask_widevine_install";
inline constexpr char kShowBookmarksButton[] = "qorai.show_bookmarks_button";
inline constexpr char kShowSidePanelButton[] = "qorai.show_side_panel_button";
inline constexpr char kLocationBarIsWide[] = "qorai.location_bar_is_wide";
inline constexpr char kReferralDownloadID[] = "qorai.referral.download_id";
inline constexpr char kReferralTimestamp[] = "qorai.referral.timestamp";
inline constexpr char kReferralAttemptTimestamp[] =
    "qorai.referral.referral_attempt_timestamp";
inline constexpr char kReferralAttemptCount[] =
    "qorai.referral.referral_attempt_count";
inline constexpr char kReferralAndroidFirstRunTimestamp[] =
    "qorai.referral_android_first_run_timestamp";
inline constexpr char kNoScriptControlType[] = "qorai.no_script_default";
inline constexpr char kShieldsAdvancedViewEnabled[] =
    "qorai.shields.advanced_view_enabled";
inline constexpr char kShieldsStatsBadgeVisible[] =
    "qorai.shields.stats_badge_visible";
inline constexpr char kAdControlType[] = "qorai.ad_default";
inline constexpr char kGoogleLoginControlType[] = "qorai.google_login_default";
// Deprecated
inline constexpr char kWebTorrentEnabled[] = "qorai.webtorrent_enabled";
inline constexpr char kHangoutsEnabled[] = "qorai.hangouts_enabled";
inline constexpr char kNewTabPageShowClock[] = "qorai.new_tab_page.show_clock";
inline constexpr char kNewTabPageClockFormat[] =
    "qorai.new_tab_page.clock_format";
inline constexpr char kNewTabPageShowStats[] = "qorai.new_tab_page.show_stats";
inline constexpr char kNewTabPageShowRewards[] =
    "qorai.new_tab_page.show_rewards";
inline constexpr char kNewTabPageShowQoraiTalk[] =
    "qorai.new_tab_page.show_together";
// Used to enable/disable Qorai Talk via a policy.
inline constexpr char kQoraiTalkDisabledByPolicy[] =
    "qorai.talk.disabled_by_policy";
inline constexpr char kNewTabPageShowQoraiVPN[] =
    "qorai.new_tab_page.show_qorai_vpn";
inline constexpr char kNewTabPageHideAllWidgets[] =
    "qorai.new_tab_page.hide_all_widgets";
inline constexpr char kNewTabPageShowsOptions[] =
    "qorai.new_tab_page.shows_options";
inline constexpr char kQoraiNewsIntroDismissed[] =
    "qorai.today.intro_dismissed";
inline constexpr char kQoraiDarkMode[] = "qorai.dark_mode";
inline constexpr char kQoraiShieldsSettingsVersion[] =
    "qorai.shields_settings_version";
inline constexpr char kDefaultBrowserPromptEnabled[] =
    "qorai.default_browser_prompt_enabled";

#if BUILDFLAG(ENABLE_EXTENSIONS) || BUILDFLAG(ENABLE_WEB_DISCOVERY_NATIVE)
inline constexpr char kWebDiscoveryEnabled[] = "qorai.web_discovery_enabled";
#endif
inline constexpr char kWebDiscoveryCTAState[] = "qorai.web_discovery.cta_state";
inline constexpr char kDontAskEnableWebDiscovery[] =
    "qorai.dont_ask_enable_web_discovery";
inline constexpr char kQoraiSearchVisitCount[] =
    "qorai.qorai_search_visit_count";

inline constexpr char kQoraiGCMChannelStatus[] = "qorai.gcm.channel_status";
inline constexpr char kImportDialogExtensions[] = "import_dialog_extensions";
inline constexpr char kImportDialogPayments[] = "import_dialog_payments";
inline constexpr char kMRUCyclingEnabled[] = "qorai.mru_cycling_enabled";
inline constexpr char kTabsSearchShow[] = "qorai.tabs_search_show";
inline constexpr char kTabMuteIndicatorNotClickable[] =
    "qorai.tabs.mute_indicator_not_clickable";
inline constexpr char kDontAskForCrashReporting[] =
    "qorai.dont_ask_for_crash_reporting";

// Cast extension requires a browser restart once the setting is toggled.
// kEnableMediaRouterOnRestart is used as a proxy to identify the current
// state of the switch and prefs::kEnableMediaRouter is updated to
// kEnableMediaRouterOnRestart on restart.
inline constexpr char kEnableMediaRouterOnRestart[] =
    "qorai.enable_media_router_on_restart";

#if BUILDFLAG(IS_ANDROID)
inline constexpr char kDesktopModeEnabled[] = "qorai.desktop_mode_enabled";
inline constexpr char kPlayYTVideoInBrowserEnabled[] =
    "qorai.play_yt_video_in_browser_enabled";
inline constexpr char kBackgroundVideoPlaybackEnabled[] =
    "qorai.background_video_playback";
inline constexpr char kSafetynetCheckFailed[] = "safetynetcheck.failed";
inline constexpr char kSafetynetStatus[] = "safetynet.status";
#endif

#if !BUILDFLAG(IS_ANDROID)
inline constexpr char kEnableWindowClosingConfirm[] =
    "qorai.enable_window_closing_confirm";
inline constexpr char kEnableClosingLastTab[] = "qorai.enable_closing_last_tab";
inline constexpr char kShowFullscreenReminder[] =
    "qorai.show_fullscreen_reminder";
#endif

inline constexpr char kDefaultBrowserLaunchingCount[] =
    "qorai.default_browser.launching_count";

// deprecated
inline constexpr char kOtherBookmarksMigrated[] =
    "qorai.other_bookmarks_migrated";

// Obsolete widget removal prefs
#if !BUILDFLAG(IS_IOS) && !BUILDFLAG(IS_ANDROID)
inline constexpr char kFTXAccessToken[] = "qorai.ftx.access_token";
inline constexpr char kFTXOauthHost[] = "qorai.ftx.oauth_host";
inline constexpr char kFTXNewTabPageShowFTX[] = "ftx.new_tab_page.show_ftx";
inline constexpr char kCryptoDotComNewTabPageShowCryptoDotCom[] =
    "crypto_dot_com.new_tab_page.show_crypto_dot_com";
inline constexpr char kCryptoDotComHasBoughtCrypto[] =
    "crypto_dot_com.new_tab_page.has_bought_crypto";
inline constexpr char kCryptoDotComHasInteracted[] =
    "crypto_dot_com.new_tab_page.has_interacted";
inline constexpr char kGeminiAccessToken[] = "qorai.gemini.access_token";
inline constexpr char kGeminiRefreshToken[] = "qorai.gemini.refresh_token";
inline constexpr char kNewTabPageShowGemini[] =
    "qorai.new_tab_page.show_gemini";
#endif

#if !BUILDFLAG(IS_IOS)
inline constexpr char kBinanceAccessToken[] = "qorai.binance.access_token";
inline constexpr char kBinanceRefreshToken[] = "qorai.binance.refresh_token";
inline constexpr char kNewTabPageShowBinance[] =
    "qorai.new_tab_page.show_binance";
inline constexpr char kQoraiSuggestedSiteSuggestionsEnabled[] =
    "qorai.qorai_suggested_site_suggestions_enabled";
#endif

#endif  // QORAI_COMPONENTS_CONSTANTS_PREF_NAMES_H_
