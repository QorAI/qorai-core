/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/extensions/api/settings_private/qorai_prefs_util.h"

#include "qorai/browser/ui/tabs/qorai_tab_prefs.h"
#include "qorai/common/pref_names.h"
#include "qorai/components/ai_chat/core/common/pref_names.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/qorai_shields/core/common/pref_names.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_wallet/browser/pref_names.h"
#include "qorai/components/qorai_wayback_machine/buildflags/buildflags.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/de_amp/common/pref_names.h"
#include "qorai/components/debounce/core/common/pref_names.h"
#include "qorai/components/decentralized_dns/core/pref_names.h"
#include "qorai/components/ntp_background_images/common/pref_names.h"
#include "qorai/components/omnibox/browser/qorai_omnibox_prefs.h"
#include "qorai/components/playlist/core/common/pref_names.h"
#include "qorai/components/request_otr/common/pref_names.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "qorai/components/tor/buildflags/buildflags.h"
#include "qorai/components/web_discovery/buildflags/buildflags.h"
#include "qorai/components/webcompat_reporter/common/pref_names.h"
#include "chrome/browser/extensions/api/settings_private/prefs_util.h"
#include "chrome/common/extensions/api/settings_private.h"
#include "chrome/common/pref_names.h"
#include "components/bookmarks/common/bookmark_pref_names.h"
#include "components/browsing_data/core/pref_names.h"
#include "components/gcm_driver/gcm_buildflags.h"
#include "components/omnibox/browser/omnibox_prefs.h"
#include "components/search_engines/search_engines_pref_names.h"
#include "extensions/buildflags/buildflags.h"

#if BUILDFLAG(ENABLE_QORAI_WAYBACK_MACHINE)
#include "qorai/components/qorai_wayback_machine/pref_names.h"
#endif

#if defined(TOOLKIT_VIEWS)
#include "qorai/components/sidebar/browser/pref_names.h"
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "qorai/components/speedreader/speedreader_pref_names.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/components/tor/pref_names.h"
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/components/qorai_vpn/common/pref_names.h"
#endif

#if BUILDFLAG(IS_WIN)
#include "qorai/components/windows_recall/windows_recall.h"
#endif

namespace extensions {

using ntp_background_images::prefs::kNewTabPageShowBackgroundImage;
using ntp_background_images::prefs::
    kNewTabPageShowSponsoredImagesBackgroundImage;

namespace settings_api = api::settings_private;

const PrefsUtil::TypedPrefMap& QoraiPrefsUtil::GetAllowlistedKeys() {
  // Static cache, similar to parent class
  static PrefsUtil::TypedPrefMap* s_qorai_allowlist = nullptr;
  if (s_qorai_allowlist) {
    return *s_qorai_allowlist;
  }
  s_qorai_allowlist = new PrefsUtil::TypedPrefMap();
  // Start with parent class allowlist
  const auto chromium_prefs = PrefsUtil::GetAllowlistedKeys();
  s_qorai_allowlist->insert(chromium_prefs.begin(), chromium_prefs.end());
  // Add Qorai values to the allowlist
  // import data
  (*s_qorai_allowlist)[kImportDialogExtensions] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kImportDialogPayments] =
      settings_api::PrefType::kBoolean;
  // Default Qorai shields
  (*s_qorai_allowlist)[kShieldsAdvancedViewEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kShieldsStatsBadgeVisible] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kAdControlType] = settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kGoogleLoginControlType] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[qorai_shields::prefs::kFBEmbedControlType] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[qorai_shields::prefs::kTwitterEmbedControlType] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[qorai_shields::prefs::kLinkedInEmbedControlType] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[qorai_shields::prefs::kReduceLanguageEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[qorai_shields::prefs::kAdBlockDeveloperMode] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[qorai_shields::prefs::kAdBlockOnlyModeEnabled] =
      settings_api::PrefType::kBoolean;

  // Webcompat Reporter
  (*s_qorai_allowlist)[webcompat_reporter::prefs::kContactInfoSaveFlagPrefs] =
      settings_api::PrefType::kBoolean;

  // Rewards/Ads prefs
  (*s_qorai_allowlist)[qorai_rewards::prefs::kEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[qorai_rewards::prefs::kShowLocationBarButton] =
      settings_api::PrefType::kBoolean;

  // Search engine prefs
  (*s_qorai_allowlist)[prefs::kAddOpenSearchEngines] =
      settings_api::PrefType::kBoolean;

  // autofill prefs
  (*s_qorai_allowlist)[kQoraiAutofillPrivateWindows] =
      settings_api::PrefType::kBoolean;

  // appearance prefs
  (*s_qorai_allowlist)[kShowBookmarksButton] = settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kShowSidePanelButton] = settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[qorai_news::prefs::kShouldShowToolbarButton] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kLocationBarIsWide] = settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[omnibox::kAutocompleteEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[omnibox::kOnDeviceSuggestionsEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[omnibox::kHistorySuggestionsEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[omnibox::kBookmarkSuggestionsEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[omnibox::kCommanderSuggestionsEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kAskEnableWidvine] = settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kTabsSearchShow] = settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[qorai_tabs::kTabHoverMode] =
      settings_api::PrefType::kNumber;
  (*s_qorai_allowlist)[kTabMuteIndicatorNotClickable] =
      settings_api::PrefType::kBoolean;
#if BUILDFLAG(IS_MAC)
  (*s_qorai_allowlist)[prefs::kShowFullscreenToolbar] =
      settings_api::PrefType::kBoolean;
#endif
#if BUILDFLAG(ENABLE_QORAI_VPN)
  (*s_qorai_allowlist)[qorai_vpn::prefs::kQoraiVPNShowButton] =
      settings_api::PrefType::kBoolean;
#if BUILDFLAG(ENABLE_QORAI_VPN_WIREGUARD)
  (*s_qorai_allowlist)[qorai_vpn::prefs::kQoraiVPNWireguardEnabled] =
      settings_api::PrefType::kBoolean;
#endif
#endif
#if defined(TOOLKIT_VIEWS)
  (*s_qorai_allowlist)[sidebar::kSidebarShowOption] =
      settings_api::PrefType::kNumber;
#endif
#if BUILDFLAG(ENABLE_SPEEDREADER)
  (*s_qorai_allowlist)[speedreader::kSpeedreaderEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[speedreader::kSpeedreaderAllowedForAllReadableSites] =
      settings_api::PrefType::kBoolean;
#endif
  // De-AMP feature
  (*s_qorai_allowlist)[de_amp::kDeAmpPrefEnabled] =
      settings_api::PrefType::kBoolean;
  // Debounce feature
  (*s_qorai_allowlist)[debounce::prefs::kDebounceEnabled] =
      settings_api::PrefType::kBoolean;
  // new tab prefs
  (*s_qorai_allowlist)[kNewTabPageShowSponsoredImagesBackgroundImage] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kNewTabPageShowBackgroundImage] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kNewTabPageShowClock] = settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kNewTabPageShowStats] = settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kNewTabPageShowRewards] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kNewTabPageShowQoraiTalk] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kNewTabPageShowQoraiVPN] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kNewTabPageShowsOptions] =
      settings_api::PrefType::kNumber;
#if BUILDFLAG(ENABLE_EXTENSIONS) || BUILDFLAG(ENABLE_WEB_DISCOVERY_NATIVE)
  // Web discovery prefs
  (*s_qorai_allowlist)[kWebDiscoveryEnabled] = settings_api::PrefType::kBoolean;
#endif
  // Clear browsing data on exit prefs.
  (*s_qorai_allowlist)[browsing_data::prefs::kDeleteBrowsingHistoryOnExit] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[browsing_data::prefs::kDeleteDownloadHistoryOnExit] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[browsing_data::prefs::kDeleteCacheOnExit] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[browsing_data::prefs::kDeleteCookiesOnExit] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[browsing_data::prefs::kDeletePasswordsOnExit] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[browsing_data::prefs::kDeleteFormDataOnExit] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[browsing_data::prefs::kDeleteSiteSettingsOnExit] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[browsing_data::prefs::kDeleteHostedAppsDataOnExit] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[browsing_data::prefs::kDeleteQoraiQoraHistory] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[browsing_data::prefs::kDeleteQoraiQoraHistoryOnExit] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[bookmarks::prefs::kAlwaysShowBookmarkBarOnNTP] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kMRUCyclingEnabled] = settings_api::PrefType::kBoolean;
#if BUILDFLAG(ENABLE_QORAI_WAYBACK_MACHINE)
  (*s_qorai_allowlist)[kQoraiWaybackMachineEnabled] =
      settings_api::PrefType::kBoolean;
#endif
  (*s_qorai_allowlist)[kEnableWindowClosingConfirm] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kEnableClosingLastTab] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kShowFullscreenReminder] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kWebViewRoundedCorners] =
      settings_api::PrefType::kBoolean;

  // Qorai Wallet pref
  (*s_qorai_allowlist)[kQoraiWalletSelectedNetworks] =
      settings_api::PrefType::kDictionary;
  (*s_qorai_allowlist)[kDefaultEthereumWallet] =
      settings_api::PrefType::kNumber;
  (*s_qorai_allowlist)[kDefaultSolanaWallet] = settings_api::PrefType::kNumber;
  (*s_qorai_allowlist)[kDefaultCardanoWallet] = settings_api::PrefType::kNumber;
  (*s_qorai_allowlist)[kDefaultBaseCurrency] = settings_api::PrefType::kString;
  (*s_qorai_allowlist)[kDefaultBaseCryptocurrency] =
      settings_api::PrefType::kString;
  (*s_qorai_allowlist)[kShowWalletIconOnToolbar] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kQoraiWalletAutoLockMinutes] =
      settings_api::PrefType::kNumber;
  (*s_qorai_allowlist)[kQoraiWalletTransactionSimulationOptInStatus] =
      settings_api::PrefType::kNumber;
  (*s_qorai_allowlist)[kQoraiWalletNftDiscoveryEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[kQoraiWalletPrivateWindowsEnabled] =
      settings_api::PrefType::kBoolean;

  // Qora Assistant pref
  (*s_qorai_allowlist)[ai_chat::prefs::kQoraiChatStorageEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[ai_chat::prefs::kQoraiChatAutocompleteProviderEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[ai_chat::prefs::kQoraiAIChatContextMenuEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[ai_chat::prefs::kQoraiAIChatShowToolbarButton] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[ai_chat::prefs::kQoraiAIChatTabOrganizationEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[ai_chat::prefs::kQoraiAIChatUserCustomizationEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[ai_chat::prefs::kQoraiAIChatUserMemoryEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[ai_chat::prefs::kQoraiAIChatOllamaFetchEnabled] =
      settings_api::PrefType::kBoolean;

  // Survey Panelist pref
  (*s_qorai_allowlist)
      [ntp_background_images::prefs::kNewTabPageSponsoredImagesSurveyPanelist] =
          settings_api::PrefType::kBoolean;

#if !BUILDFLAG(USE_GCM_FROM_PLATFORM)
  // Push Messaging Pref
  (*s_qorai_allowlist)[kQoraiGCMChannelStatus] =
      settings_api::PrefType::kBoolean;
#endif
  // Omnibox pref
  (*s_qorai_allowlist)[omnibox::kPreventUrlElisionsInOmnibox] =
      settings_api::PrefType::kBoolean;
#if BUILDFLAG(ENABLE_TOR)
  (*s_qorai_allowlist)[tor::prefs::kOnionOnlyInTorWindows] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[tor::prefs::kBridgesConfig] =
      settings_api::PrefType::kDictionary;
#endif
  (*s_qorai_allowlist)[prefs::kWebRTCIPHandlingPolicy] =
      settings_api::PrefType::kString;
  // Request OTR feature
  (*s_qorai_allowlist)[request_otr::kRequestOTRActionOption] =
      settings_api::PrefType::kNumber;

  (*s_qorai_allowlist)[decentralized_dns::kUnstoppableDomainsResolveMethod] =
      settings_api::PrefType::kNumber;
  (*s_qorai_allowlist)[decentralized_dns::kENSResolveMethod] =
      settings_api::PrefType::kNumber;
  (*s_qorai_allowlist)[decentralized_dns::kEnsOffchainResolveMethod] =
      settings_api::PrefType::kNumber;
  (*s_qorai_allowlist)[decentralized_dns::kSnsResolveMethod] =
      settings_api::PrefType::kNumber;

  // Media router pref
  (*s_qorai_allowlist)[kEnableMediaRouterOnRestart] =
      settings_api::PrefType::kBoolean;

#if defined(TOOLKIT_VIEWS)
  // Vertical tab strip prefs
  (*s_qorai_allowlist)[qorai_tabs::kVerticalTabsEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[qorai_tabs::kVerticalTabsFloatingEnabled] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[qorai_tabs::kVerticalTabsShowTitleOnWindow] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[qorai_tabs::kVerticalTabsOnRight] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[qorai_tabs::kVerticalTabsShowScrollbar] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[qorai_tabs::kVerticalTabsExpandedStatePerWindow] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[qorai_tabs::kVerticalTabsHideCompletelyWhenCollapsed] =
      settings_api::PrefType::kBoolean;
#endif

  (*s_qorai_allowlist)[playlist::kPlaylistEnabledPref] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[playlist::kPlaylistCacheByDefault] =
      settings_api::PrefType::kBoolean;

#if !BUILDFLAG(IS_ANDROID)
  (*s_qorai_allowlist)[qorai_tabs::kSharedPinnedTab] =
      settings_api::PrefType::kBoolean;
  (*s_qorai_allowlist)[qorai_tabs::kTreeTabsEnabled] =
      settings_api::PrefType::kBoolean;
#endif

#if BUILDFLAG(IS_WIN)
  (*s_qorai_allowlist)[windows_recall::prefs::kWindowsRecallDisabled] =
      settings_api::PrefType::kBoolean;
#endif

  return *s_qorai_allowlist;
}

}  // namespace extensions
