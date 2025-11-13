/* Copyright (c) 2019 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/feature_list.h"
#include "qorai/browser/metrics/buildflags/buildflags.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/qorai_shields/core/common/features.h"
#include "qorai/components/qorai_shields/core/common/pref_names.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_utils.h"
#include "qorai/components/qorai_wallet/browser/pref_names.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/components/qorai_wayback_machine/buildflags/buildflags.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/global_privacy_control/pref_names.h"
#include "qorai/components/ntp_background_images/buildflags/buildflags.h"
#include "qorai/components/query_filter/pref_names.h"
#include "build/build_config.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/prefetch/pref_names.h"
#include "chrome/browser/preloading/preloading_prefs.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/webui/new_tab_page/ntp_pref_names.h"
#include "chrome/common/pref_names.h"
#include "chrome/test/base/chrome_test_utils.h"
#include "chrome/test/base/platform_browser_test.h"
#include "components/embedder_support/pref_names.h"
#include "components/gcm_driver/gcm_buildflags.h"
#include "components/ntp_tiles/tile_type.h"
#include "components/omnibox/browser/aim_eligibility_service.h"
#include "components/omnibox/browser/omnibox_prefs.h"
#include "components/policy/core/common/policy_pref_names.h"
#include "components/prefs/pref_service.h"
#include "components/safe_browsing/core/common/safe_browsing_prefs.h"
#include "components/signin/public/base/signin_pref_names.h"
#include "components/spellcheck/browser/pref_names.h"
#include "components/sync/base/pref_names.h"
#include "content/public/test/browser_test.h"

#if BUILDFLAG(ENABLE_QORAI_WAYBACK_MACHINE)
#include "qorai/components/qorai_wayback_machine/pref_names.h"
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/components/qorai_vpn/common/pref_names.h"
#endif

#if !BUILDFLAG(IS_ANDROID)
#include "chrome/browser/ui/webui/bookmarks/bookmark_prefs.h"
#include "chrome/browser/ui/webui/side_panel/bookmarks/bookmarks.mojom.h"
#endif

#if BUILDFLAG(ENABLE_CUSTOM_BACKGROUND)
#include "qorai/browser/ntp_background/ntp_background_prefs.h"
#endif

using QorAIProfilePrefsBrowserTest = PlatformBrowserTest;
using QorAILocalStatePrefsBrowserTest = PlatformBrowserTest;

// Check download prompt preference is set to true by default.
IN_PROC_BROWSER_TEST_F(QorAIProfilePrefsBrowserTest, DownloadPromptDefault) {
  EXPECT_TRUE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      prefs::kPromptForDownload));
}

IN_PROC_BROWSER_TEST_F(QorAIProfilePrefsBrowserTest, MiscQorAIPrefs) {
  EXPECT_FALSE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      kShieldsAdvancedViewEnabled));
  EXPECT_TRUE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      kShieldsStatsBadgeVisible));
  EXPECT_TRUE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      kAdControlType));
  EXPECT_TRUE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      kGoogleLoginControlType));
  EXPECT_TRUE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      query_filter::kTrackingQueryParametersFilteringEnabled));
  EXPECT_TRUE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      global_privacy_control::kGlobalPrivacyControlEnabled));
  EXPECT_TRUE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      qorai_shields::prefs::kFBEmbedControlType));
  EXPECT_TRUE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      qorai_shields::prefs::kTwitterEmbedControlType));
  EXPECT_FALSE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      qorai_shields::prefs::kLinkedInEmbedControlType));
  EXPECT_EQ(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
                qorai_shields::prefs::kReduceLanguageEnabled),
            base::FeatureList::IsEnabled(
                qorai_shields::features::kQorAIReduceLanguage));
#if BUILDFLAG(ENABLE_QORAI_WAYBACK_MACHINE)
  EXPECT_TRUE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      kQorAIWaybackMachineEnabled));
#endif
  EXPECT_TRUE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      qorai_rewards::prefs::kShowLocationBarButton));
  EXPECT_EQ(qorai_wallet::GetDefaultEthereumWallet(
                chrome_test_utils::GetProfile(this)->GetPrefs()),
            qorai_wallet::mojom::DefaultWallet::QorAIWalletPreferExtension);
  EXPECT_EQ(qorai_wallet::GetDefaultSolanaWallet(
                chrome_test_utils::GetProfile(this)->GetPrefs()),
            qorai_wallet::mojom::DefaultWallet::QorAIWalletPreferExtension);
  EXPECT_EQ(qorai_wallet::GetDefaultCardanoWallet(
                chrome_test_utils::GetProfile(this)->GetPrefs()),
            qorai_wallet::mojom::DefaultWallet::QorAIWallet);
  EXPECT_TRUE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      kShowWalletIconOnToolbar));
  EXPECT_FALSE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      kMRUCyclingEnabled));
#if !BUILDFLAG(USE_GCM_FROM_PLATFORM)
  EXPECT_FALSE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      kQorAIGCMChannelStatus));
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
  EXPECT_TRUE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      qorai_vpn::prefs::kQorAIVPNShowButton));
#endif

#if BUILDFLAG(ENABLE_CUSTOM_BACKGROUND)
  EXPECT_FALSE(chrome_test_utils::GetProfile(this)->GetPrefs()->HasPrefPath(
      NTPBackgroundPrefs::kDeprecatedPrefName));
#endif

#if !BUILDFLAG(IS_ANDROID)
  EXPECT_EQ(static_cast<int>(side_panel::mojom::ViewType::kCompact),
            chrome_test_utils::GetProfile(this)->GetPrefs()->GetInteger(
                bookmarks_webui::prefs::kBookmarksViewType));
#endif
}

IN_PROC_BROWSER_TEST_F(QorAIProfilePrefsBrowserTest,
                       DisableGoogleServicesByDefault) {
#if defined(TOOLKIT_VIEWS)
  constexpr char kSideSearchEnabled[] = "side_search.enabled";
  EXPECT_FALSE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      kSideSearchEnabled));
#endif
  EXPECT_FALSE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      embedder_support::kAlternateErrorPagesEnabled));
  EXPECT_FALSE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      spellcheck::prefs::kSpellCheckUseSpellingService));
  EXPECT_FALSE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      prefs::kSafeBrowsingExtendedReportingOptInAllowed));
#if !BUILDFLAG(IS_ANDROID)
  EXPECT_FALSE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      prefs::kSearchSuggestEnabled));
#endif
  EXPECT_EQ(chrome_test_utils::GetProfile(this)->GetPrefs()->GetInteger(
                prefetch::prefs::kNetworkPredictionOptions),
            static_cast<int>(prefetch::NetworkPredictionOptions::kDisabled));
  EXPECT_FALSE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      prefs::kSigninAllowedOnNextStartup));
  // Verify cloud print is disabled.
  EXPECT_FALSE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      prefs::kCloudPrintProxyEnabled));
#if !BUILDFLAG(IS_ANDROID)
  EXPECT_EQ(chrome_test_utils::GetProfile(this)->GetPrefs()->GetInteger(
                ntp_prefs::kNtpShortcutsType),
            static_cast<int>(ntp_tiles::TileType::kTopSites));
#endif
  EXPECT_TRUE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      policy::policy_prefs::kHideWebStoreIcon));

  EXPECT_FALSE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      prefs::kSplitViewDragAndDropEnabled));
}

IN_PROC_BROWSER_TEST_F(QorAIProfilePrefsBrowserTest, MediaRouterPrefTest) {
  EXPECT_TRUE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      ::prefs::kEnableMediaRouter));
  EXPECT_TRUE(chrome_test_utils::GetProfile(this)->GetPrefs()->GetBoolean(
      kEnableMediaRouterOnRestart));
}

IN_PROC_BROWSER_TEST_F(QorAIProfilePrefsBrowserTest, AIModePrefTest) {
  EXPECT_EQ(-1, chrome_test_utils::GetProfile(this)->GetPrefs()->GetInteger(
                    ::omnibox::kAIModeSettings));
  EXPECT_FALSE(AimEligibilityService::IsAimAllowedByPolicy(
      chrome_test_utils::GetProfile(this)->GetPrefs()));
}

IN_PROC_BROWSER_TEST_F(QorAILocalStatePrefsBrowserTest, DefaultLocalStateTest) {
#if BUILDFLAG(ENABLE_CRASH_DIALOG)
  EXPECT_FALSE(
      g_browser_process->local_state()->GetBoolean(kDontAskForCrashReporting));
#endif
}
