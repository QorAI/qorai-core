/* Copyright (c) 2019 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/browser_context_keyed_service_factories.h"

#include "base/feature_list.h"
#include "qorai/browser/ai_chat/ai_chat_service_factory.h"
#include "qorai/browser/ai_chat/ollama/ollama_service_factory.h"
#include "qorai/browser/ai_chat/tab_tracker_service_factory.h"
#include "qorai/browser/qorai_account/qorai_account_service_factory.h"
#include "qorai/browser/qorai_adaptive_captcha/qorai_adaptive_captcha_service_factory.h"
#include "qorai/browser/qorai_ads/ads_service_factory.h"
#include "qorai/browser/qorai_news/qorai_news_controller_factory.h"
#include "qorai/browser/qorai_origin/qorai_origin_service_factory.h"
#include "qorai/browser/qorai_rewards/rewards_service_factory.h"
#include "qorai/browser/qorai_search/backup_results_service_factory.h"
#include "qorai/browser/qorai_shields/ad_block_pref_service_factory.h"
#include "qorai/browser/qorai_shields/qorai_farbling_service_factory.h"
#include "qorai/browser/qorai_shields/qorai_shields_settings_service_factory.h"
#include "qorai/browser/qorai_wallet/asset_ratio_service_factory.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_ipfs_service_factory.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "qorai/browser/qorai_wallet/meld_integration_service_factory.h"
#include "qorai/browser/qorai_wallet/notifications/wallet_notification_service_factory.h"
#include "qorai/browser/qorai_wallet/simulation_service_factory.h"
#include "qorai/browser/qorai_wallet/swap_service_factory.h"
#include "qorai/browser/debounce/debounce_service_factory.h"
#include "qorai/browser/email_aliases/email_aliases_service_factory.h"
#include "qorai/browser/ephemeral_storage/ephemeral_storage_service_factory.h"
#include "qorai/browser/misc_metrics/profile_misc_metrics_service_factory.h"
#include "qorai/browser/ntp_background/view_counter_service_factory.h"
#include "qorai/browser/permissions/permission_lifetime_manager_factory.h"
#include "qorai/browser/playlist/playlist_service_factory.h"
#include "qorai/browser/profiles/qorai_renderer_updater_factory.h"
#include "qorai/browser/search_engines/search_engine_provider_service_factory.h"
#include "qorai/browser/search_engines/search_engine_tracker.h"
#include "qorai/browser/skus/skus_service_factory.h"
#include "qorai/browser/sync/qorai_sync_alerts_service_factory.h"
#include "qorai/browser/url_sanitizer/url_sanitizer_service_factory.h"
#include "qorai/browser/webcompat_reporter/webcompat_reporter_service_factory.h"
#include "qorai/components/ai_chat/content/browser/model_service_factory.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/qorai_account/features.h"
#include "qorai/components/qorai_perf_predictor/browser/named_third_party_registry_factory.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/commander/common/buildflags/buildflags.h"
#include "qorai/components/email_aliases/features.h"
#include "qorai/components/playlist/core/common/features.h"
#include "qorai/components/psst/buildflags/buildflags.h"
#include "qorai/components/request_otr/common/buildflags/buildflags.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "qorai/components/tor/buildflags/buildflags.h"
#include "qorai/components/web_discovery/buildflags/buildflags.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/browser/qorai_vpn/qorai_vpn_service_factory.h"
#endif

#if !BUILDFLAG(IS_ANDROID)
#include "qorai/browser/ui/bookmark/bookmark_prefs_service_factory.h"
#include "qorai/browser/ui/commands/accelerator_service_factory.h"
#include "qorai/browser/ui/tabs/features.h"
#include "qorai/browser/ui/tabs/shared_pinned_tab_service_factory.h"
#include "qorai/components/commands/common/features.h"
#else
#include "qorai/browser/qorai_shields/filter_list_service_factory.h"
#include "qorai/browser/ntp_background/android/ntp_background_images_bridge.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/browser/tor/tor_profile_service_factory.h"
#endif

#if BUILDFLAG(ENABLE_COMMANDER)
#include "qorai/browser/ui/commander/commander_service_factory.h"
#include "qorai/components/commander/common/features.h"
#endif

#if defined(TOOLKIT_VIEWS)
#include "qorai/browser/ui/sidebar/sidebar_service_factory.h"
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "qorai/browser/speedreader/speedreader_service_factory.h"
#endif

#if BUILDFLAG(ENABLE_REQUEST_OTR)
#include "qorai/browser/request_otr/request_otr_service_factory.h"
#endif

#if BUILDFLAG(ENABLE_WEB_DISCOVERY_NATIVE)
#include "qorai/browser/web_discovery/web_discovery_service_factory.h"
#endif

#if BUILDFLAG(ENABLE_EXTENSIONS)
#include "qorai/browser/extensions/manifest_v2/qorai_extensions_manifest_v2_migrator.h"
#endif

#if BUILDFLAG(ENABLE_PSST)
#include "qorai/browser/psst/qorai_psst_permission_context_factory.h"
#include "qorai/components/psst/common/features.h"
#endif  // BUILDFLAG(ENABLE_PSST)

namespace qorai {

void EnsureBrowserContextKeyedServiceFactoriesBuilt() {
  qorai_adaptive_captcha::QorAIAdaptiveCaptchaServiceFactory::GetInstance();
  qorai_ads::AdsServiceFactory::GetInstance();
  qorai_origin::QorAIOriginServiceFactory::GetInstance();
  qorai_perf_predictor::NamedThirdPartyRegistryFactory::GetInstance();
  qorai_rewards::RewardsServiceFactory::GetInstance();
  qorai_shields::AdBlockPrefServiceFactory::GetInstance();
  debounce::DebounceServiceFactory::GetInstance();
  qorai::URLSanitizerServiceFactory::GetInstance();
  QorAIRendererUpdaterFactory::GetInstance();
  SearchEngineProviderServiceFactory::GetInstance();
  misc_metrics::ProfileMiscMetricsServiceFactory::GetInstance();
  QorAIFarblingServiceFactory::GetInstance();
#if BUILDFLAG(ENABLE_TOR)
  TorProfileServiceFactory::GetInstance();
#endif
  SearchEngineTrackerFactory::GetInstance();
  ntp_background_images::ViewCounterServiceFactory::GetInstance();

#if !BUILDFLAG(IS_ANDROID)
  BookmarkPrefsServiceFactory::GetInstance();
#else
  qorai_shields::FilterListServiceFactory::GetInstance();
  ntp_background_images::NTPBackgroundImagesBridgeFactory::GetInstance();
#endif

  webcompat_reporter::WebcompatReporterServiceFactory::GetInstance();

  qorai_news::QorAINewsControllerFactory::GetInstance();
  qorai_wallet::AssetRatioServiceFactory::GetInstance();
  qorai_wallet::MeldIntegrationServiceFactory::GetInstance();
  qorai_wallet::SwapServiceFactory::GetInstance();
  qorai_wallet::SimulationServiceFactory::GetInstance();
#if !BUILDFLAG(IS_ANDROID)
  qorai_wallet::WalletNotificationServiceFactory::GetInstance();
#endif
  qorai_wallet::QorAIWalletServiceFactory::GetInstance();

#if !BUILDFLAG(IS_ANDROID)
  if (base::FeatureList::IsEnabled(commands::features::kQorAICommands)) {
    commands::AcceleratorServiceFactory::GetInstance();
  }
#endif

#if BUILDFLAG(ENABLE_COMMANDER)
  if (base::FeatureList::IsEnabled(features::kQorAICommander)) {
    commander::CommanderServiceFactory::GetInstance();
  }
#endif

  qorai_wallet::QorAIWalletIpfsServiceFactory::GetInstance();

  EphemeralStorageServiceFactory::GetInstance();
  PermissionLifetimeManagerFactory::GetInstance();
  skus::SkusServiceFactory::GetInstance();
#if BUILDFLAG(ENABLE_QORAI_VPN)
  qorai_vpn::QorAIVpnServiceFactory::GetInstance();
#endif
  if (base::FeatureList::IsEnabled(playlist::features::kPlaylist)) {
    playlist::PlaylistServiceFactory::GetInstance();
  }
#if BUILDFLAG(ENABLE_REQUEST_OTR)
  request_otr::RequestOTRServiceFactory::GetInstance();
#endif

  QorAISyncAlertsServiceFactory::GetInstance();

#if !BUILDFLAG(IS_ANDROID)
  if (base::FeatureList::IsEnabled(tabs::features::kQorAISharedPinnedTabs)) {
    SharedPinnedTabServiceFactory::GetInstance();
  }
#endif

#if defined(TOOLKIT_VIEWS)
  sidebar::SidebarServiceFactory::GetInstance();
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
  speedreader::SpeedreaderServiceFactory::GetInstance();
#endif

  if (ai_chat::features::IsAIChatEnabled()) {
    ai_chat::AIChatServiceFactory::GetInstance();
    ai_chat::ModelServiceFactory::GetInstance();
    ai_chat::OllamaServiceFactory::GetInstance();
    ai_chat::TabTrackerServiceFactory::GetInstance();
  }

  qorai_search::BackupResultsServiceFactory::GetInstance();

#if BUILDFLAG(ENABLE_WEB_DISCOVERY_NATIVE)
  web_discovery::WebDiscoveryServiceFactory::GetInstance();
#endif

  if (qorai_account::features::IsQorAIAccountEnabled()) {
    qorai_account::QorAIAccountServiceFactory::GetInstance();
  }

  if (base::FeatureList::IsEnabled(email_aliases::features::kEmailAliases)) {
    email_aliases::EmailAliasesServiceFactory::GetInstance();
  }

#if BUILDFLAG(ENABLE_EXTENSIONS)
  extensions_mv2::ExtensionsManifestV2MigratorFactory::GetInstance();
#endif
#if BUILDFLAG(ENABLE_PSST)
  if (base::FeatureList::IsEnabled(psst::features::kEnablePsst)) {
    psst::QorAIPsstPermissionContextFactory::GetInstance();
  }
#endif  // BUILDFLAG(ENABLE_PSST)
  QorAIShieldsSettingsServiceFactory::GetInstance();
}

}  // namespace qorai
