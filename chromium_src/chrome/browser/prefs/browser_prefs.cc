/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/check.h"
#include "qorai/browser/qorai_local_state_prefs.h"
#include "qorai/browser/qorai_profile_prefs.h"
#include "qorai/browser/qorai_rewards/rewards_prefs_util.h"
#include "qorai/browser/qorai_stats/qorai_stats_updater.h"
#include "qorai/browser/misc_metrics/uptime_monitor_impl.h"
#include "qorai/browser/themes/qorai_dark_mode_utils.h"
#include "qorai/browser/translate/qorai_translate_prefs_migration.h"
#include "qorai/components/ai_chat/core/browser/model_service.h"
#include "qorai/components/qorai_adaptive_captcha/prefs_util.h"
#include "qorai/components/qorai_ads/core/public/prefs/obsolete_pref_util.h"
#include "qorai/components/qorai_news/browser/qorai_news_p3a.h"
#include "qorai/components/qorai_news/common/p3a_pref_names.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/qorai_search_conversion/p3a.h"
#include "qorai/components/qorai_shields/content/browser/ad_block_service.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_p3a.h"
#include "qorai/components/qorai_sync/qorai_sync_prefs.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_prefs.h"
#include "qorai/components/qorai_wallet/browser/keyring_service.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/decentralized_dns/core/utils.h"
#include "qorai/components/ipfs/ipfs_prefs.h"
#include "qorai/components/l10n/common/prefs.h"
#include "qorai/components/ntp_background_images/browser/ntp_background_images_service.h"
#include "qorai/components/ntp_background_images/buildflags/buildflags.h"
#include "qorai/components/ntp_background_images/common/view_counter_pref_registry.h"
#include "qorai/components/omnibox/browser/qorai_omnibox_prefs.h"
#include "qorai/components/p3a/metric_log_store.h"
#include "qorai/components/p3a/rotation_scheduler.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "qorai/components/tor/buildflags/buildflags.h"
#include "chrome/browser/accessibility/page_colors_controller.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/channel_info.h"
#include "chrome/common/pref_names.h"
#include "components/gcm_driver/gcm_buildflags.h"
#include "components/translate/core/browser/translate_prefs.h"
#include "extensions/buildflags/buildflags.h"
#include "third_party/widevine/cdm/buildflags.h"

#if !BUILDFLAG(IS_ANDROID)
#include "qorai/browser/ui/tabs/qorai_tab_prefs.h"
#include "qorai/browser/ui/webui/welcome_page/qorai_welcome_ui_prefs.h"
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/components/tor/pref_names.h"
#include "qorai/components/tor/tor_utils.h"
#endif

#if BUILDFLAG(ENABLE_WIDEVINE)
#include "qorai/browser/widevine/widevine_utils.h"
#endif

#if !BUILDFLAG(ENABLE_EXTENSIONS)
#define CHROME_BROWSER_WEB_APPLICATIONS_WEB_APP_PROVIDER_H_
#endif  // !BUILDFLAG(ENABLE_EXTENSIONS)

#define MigrateObsoleteProfilePrefs MigrateObsoleteProfilePrefs_ChromiumImpl
#define MigrateObsoleteLocalStatePrefs \
  MigrateObsoleteLocalStatePrefs_ChromiumImpl
#include <chrome/browser/prefs/browser_prefs.cc>
#undef MigrateObsoleteProfilePrefs
#undef MigrateObsoleteLocalStatePrefs

#if !BUILDFLAG(USE_GCM_FROM_PLATFORM)
#include "qorai/browser/gcm_driver/qorai_gcm_utils.h"
#endif

#if BUILDFLAG(ENABLE_CUSTOM_BACKGROUND)
#include "qorai/browser/ntp_background/ntp_background_prefs.h"
#endif

#if defined(TOOLKIT_VIEWS)
#include "qorai/components/sidebar/browser/pref_names.h"
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "qorai/components/speedreader/speedreader_pref_migration.h"
#endif

// This method should be periodically pruned of year+ old migrations.
void MigrateObsoleteProfilePrefs(PrefService* profile_prefs,
                                 const base::FilePath& profile_path) {
  DCHECK(profile_prefs);
  // BEGIN_MIGRATE_OBSOLETE_PROFILE_PREFS
#if !BUILDFLAG(USE_GCM_FROM_PLATFORM)
  // Added 02/2020.
  // Must be called before ChromiumImpl because it's migrating a Chromium pref
  // to Qorai pref.
  gcm::MigrateGCMPrefs(profile_prefs);
#endif

#if !BUILDFLAG(IS_ANDROID)
  // Added 06/2025.
  // Must be called before ChromiumImpl because it's migrating a Chromium pref
  // to Qorai pref.
  qorai::welcome_ui::prefs::MigratePrefs(profile_prefs);
#endif  // !BUILDFLAG(IS_ANDROID)

  MigrateObsoleteProfilePrefs_ChromiumImpl(profile_prefs, profile_path);

  qorai_sync::MigrateQoraiSyncPrefs(profile_prefs);

#if !BUILDFLAG(IS_ANDROID)
  // Added 10/2022
  profile_prefs->ClearPref(kDefaultBrowserLaunchingCount);
#endif

#if BUILDFLAG(ENABLE_EXTENSIONS)
  // Added 11/2022
  profile_prefs->ClearPref(kDontAskEnableWebDiscovery);
  profile_prefs->ClearPref(kQoraiSearchVisitCount);
#endif

  qorai_wallet::MigrateObsoleteProfilePrefs(profile_prefs);

  // Added 05/2021
  profile_prefs->ClearPref(kQoraiNewsIntroDismissed);
  // Added 07/2021
  profile_prefs->ClearPref(prefs::kNetworkPredictionOptions);

  // Added 01/2022
  qorai_rewards::MigrateObsoleteProfilePrefs(profile_prefs);

  // Added 05/2022
  translate::ClearMigrationQoraiProfilePrefs(profile_prefs);

  // Added 06/2022
#if BUILDFLAG(ENABLE_CUSTOM_BACKGROUND)
  NTPBackgroundPrefs(profile_prefs).MigrateOldPref();
#endif

  // Added 24/11/2022: https://github.com/qorai/qorai-core/pull/16027
#if !BUILDFLAG(IS_IOS) && !BUILDFLAG(IS_ANDROID)
  profile_prefs->ClearPref(kFTXAccessToken);
  profile_prefs->ClearPref(kFTXOauthHost);
  profile_prefs->ClearPref(kFTXNewTabPageShowFTX);
  profile_prefs->ClearPref(kCryptoDotComNewTabPageShowCryptoDotCom);
  profile_prefs->ClearPref(kCryptoDotComHasBoughtCrypto);
  profile_prefs->ClearPref(kCryptoDotComHasInteracted);
  profile_prefs->ClearPref(kGeminiAccessToken);
  profile_prefs->ClearPref(kGeminiRefreshToken);
  profile_prefs->ClearPref(kNewTabPageShowGemini);
#endif

  // Added 24/11/2022: https://github.com/qorai/qorai-core/pull/16027
#if !BUILDFLAG(IS_IOS)
  profile_prefs->ClearPref(kBinanceAccessToken);
  profile_prefs->ClearPref(kBinanceRefreshToken);
  profile_prefs->ClearPref(kNewTabPageShowBinance);
  profile_prefs->ClearPref(kQoraiSuggestedSiteSuggestionsEnabled);
#endif

  // Added 03/2024
#if BUILDFLAG(ENABLE_TOR)
  profile_prefs->ClearPref(tor::prefs::kAutoOnionRedirect);
#endif

#if defined(TOOLKIT_VIEWS)
  // Added May 2023
  if (profile_prefs->GetBoolean(sidebar::kSidebarAlignmentChangedTemporarily)) {
    // If temporarily changed, it means sidebar is set to right.
    // Just clear alignment prefs as default alignment is changed to right.
    profile_prefs->ClearPref(prefs::kSidePanelHorizontalAlignment);
  }

  profile_prefs->ClearPref(sidebar::kSidebarAlignmentChangedTemporarily);
#endif

  qorai_news::p3a::prefs::MigrateObsoleteProfileNewsMetricsPrefs(profile_prefs);

  // Added 2023-09
  ntp_background_images::MigrateObsoleteProfilePrefs(profile_prefs);

  // Added 2023-11
  qorai_ads::MigrateObsoleteProfilePrefs(profile_prefs);

  qorai_shields::MigrateObsoleteProfilePrefs(profile_prefs);

#if !BUILDFLAG(IS_ANDROID)
  // Added 2024-01
  qorai_tabs::MigrateQoraiProfilePrefs(profile_prefs);
#endif  // !BUILDFLAG(IS_ANDROID)

  // Added 2024-04
  ai_chat::ModelService::MigrateProfilePrefs(profile_prefs);

  // Added 2024-05
  ipfs::ClearDeprecatedIpfsPrefs(profile_prefs);

  // Added 2024-07
  profile_prefs->ClearPref(kHangoutsEnabled);

  // Added 2024-10
  qorai_adaptive_captcha::MigrateObsoleteProfilePrefs(profile_prefs);

#if BUILDFLAG(IS_ANDROID)
  // Added 27/11/2024: https://github.com/qorai/qorai-core/pull/26719
  profile_prefs->ClearPref(kSafetynetCheckFailed);
  profile_prefs->ClearPref(kSafetynetStatus);
#endif  // BUILDFLAG(IS_ANDROID)

  // Added 2025-05
#if !BUILDFLAG(IS_IOS) && !BUILDFLAG(IS_ANDROID)
  profile_prefs->ClearPref(kWebTorrentEnabled);
#endif

  // Added 2025-08 - Speedreader preference migration
#if BUILDFLAG(ENABLE_SPEEDREADER)
  speedreader::MigrateObsoleteProfilePrefs(profile_prefs);
#endif

  // END_MIGRATE_OBSOLETE_PROFILE_PREFS
}

// This method should be periodically pruned of year+ old migrations.
void MigrateObsoleteLocalStatePrefs(PrefService* local_state) {
  // BEGIN_MIGRATE_OBSOLETE_LOCAL_STATE_PREFS
  MigrateObsoleteLocalStatePrefs_ChromiumImpl(local_state);

#if BUILDFLAG(ENABLE_TOR)
  // Added 4/2021.
  tor::MigrateLastUsedProfileFromLocalStatePrefs(local_state);
#endif

  decentralized_dns::MigrateObsoleteLocalStatePrefs(local_state);

#if !BUILDFLAG(IS_ANDROID)
  // Added 10/2022
  local_state->ClearPref(kDefaultBrowserPromptEnabled);
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
  // Added 09/2024
  qorai_vpn::MigrateLocalStatePrefs(local_state);
#endif

  misc_metrics::UptimeMonitorImpl::MigrateObsoletePrefs(local_state);
  qorai_search_conversion::p3a::MigrateObsoleteLocalStatePrefs(local_state);
  qorai_shields::MigrateObsoletePrefsForAdBlockService(local_state);
  qorai_stats::MigrateObsoleteLocalStatePrefs(local_state);
  qorai_l10n::MigrateObsoleteLocalStatePrefs(local_state);
  p3a::MetricLogStore::MigrateObsoleteLocalStatePrefs(local_state);
  p3a::RotationScheduler::MigrateObsoleteLocalStatePrefs(local_state);
  qorai_ads::MigrateObsoleteLocalStatePrefs(local_state);
  ntp_background_images::NTPBackgroundImagesService::
      MigrateObsoleteLocalStatePrefs(local_state);

  // END_MIGRATE_OBSOLETE_LOCAL_STATE_PREFS
}

#if !BUILDFLAG(ENABLE_EXTENSIONS)
#undef CHROME_BROWSER_WEB_APPLICATIONS_WEB_APP_PROVIDER_H_
#endif  // !BUILDFLAG(ENABLE_EXTENSIONS)
