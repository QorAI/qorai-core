/* Copyright (c) 2019 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_tab_helpers.h"

#include <memory>
#include <utility>

#include "base/command_line.h"
#include "base/feature_list.h"
#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "qorai/browser/ai_chat/ai_chat_service_factory.h"
#include "qorai/browser/ai_chat/ai_chat_utils.h"
#include "qorai/browser/qorai_ads/creatives/search_result_ad/creative_search_result_ad_tab_helper.h"
#include "qorai/browser/qorai_ads/tabs/ads_tab_helper.h"
#include "qorai/browser/qorai_browser_process.h"
#include "qorai/browser/qorai_news/qorai_news_tab_helper.h"
#include "qorai/browser/qorai_rewards/rewards_tab_helper.h"
#include "qorai/browser/qorai_shields/qorai_shields_web_contents_observer.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_tab_helper.h"
#include "qorai/browser/ephemeral_storage/ephemeral_storage_tab_helper.h"
#include "qorai/browser/misc_metrics/page_metrics_tab_helper.h"
#include "qorai/browser/misc_metrics/process_misc_metrics.h"
#include "qorai/browser/playlist/playlist_service_factory.h"
#include "qorai/browser/ui/qorai_ui_features.h"
#include "qorai/components/ai_chat/content/browser/ai_chat_tab_helper.h"
#include "qorai/components/qorai_perf_predictor/browser/perf_predictor_tab_helper.h"
#include "qorai/components/qorai_wayback_machine/buildflags/buildflags.h"
#include "qorai/components/playlist/content/browser/playlist_tab_helper.h"
#include "qorai/components/playlist/core/common/features.h"
#include "qorai/components/request_otr/common/buildflags/buildflags.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "qorai/components/tor/buildflags/buildflags.h"
#include "qorai/components/web_discovery/buildflags/buildflags.h"
#include "build/build_config.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/chrome_isolated_world_ids.h"
#include "components/user_prefs/user_prefs.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/web_contents.h"
#include "extensions/buildflags/buildflags.h"
#include "net/base/features.h"
#include "printing/buildflags/buildflags.h"
#include "third_party/widevine/cdm/buildflags.h"

#if BUILDFLAG(IS_ANDROID)
#include "qorai/browser/android/youtube_script_injector/youtube_script_injector_tab_helper.h"
#endif

#if !BUILDFLAG(IS_ANDROID)
#include "qorai/browser/qorai_shields/qorai_shields_tab_helper.h"
#include "qorai/browser/ui/geolocation/qorai_geolocation_permission_tab_helper.h"
#include "chrome/browser/ui/thumbnails/thumbnail_tab_helper.h"
#endif

#if BUILDFLAG(IS_WIN)
#include "qorai/browser/new_tab/background_color_tab_helper.h"
#endif

#if BUILDFLAG(ENABLE_PRINT_PREVIEW)
#include "qorai/browser/ai_chat/print_preview_extractor.h"
#include "qorai/browser/ai_chat/print_preview_extractor_internal.h"
#include "chrome/browser/ui/webui/print_preview/print_preview_ui.h"
#endif  // BUILDFLAG(ENABLE_PRINT_PREVIEW)

#if BUILDFLAG(ENABLE_WIDEVINE)
#include "qorai/browser/qorai_drm_tab_helper.h"
#endif

#if BUILDFLAG(ENABLE_QORAI_WAYBACK_MACHINE)
#include "qorai/components/qorai_wayback_machine/qorai_wayback_machine_tab_helper.h"
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "qorai/browser/ui/speedreader/speedreader_tab_helper.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/components/tor/onion_location_tab_helper.h"
#include "qorai/components/tor/tor_tab_helper.h"
#endif

#if BUILDFLAG(ENABLE_EXTENSIONS) || BUILDFLAG(ENABLE_WEB_DISCOVERY_NATIVE)
#include "qorai/browser/web_discovery/web_discovery_tab_helper.h"
#endif

#if BUILDFLAG(ENABLE_REQUEST_OTR)
#include "qorai/browser/request_otr/request_otr_tab_helper.h"
#include "qorai/components/request_otr/common/features.h"
#endif

#if defined(TOOLKIT_VIEWS)
#include "qorai/browser/onboarding/onboarding_tab_helper.h"
#include "qorai/browser/ui/sidebar/sidebar_tab_helper.h"
#endif

namespace qorai {

void AttachTabHelpers(content::WebContents* web_contents) {
  // If your TabHelper is related to privacy consider whether it belongs in this
  // method, so it can also be attached to background WebContents.
  AttachPrivacySensitiveTabHelpers(web_contents);

#if BUILDFLAG(IS_ANDROID)
  YouTubeScriptInjectorTabHelper::CreateForWebContents(web_contents);
#else
  // Add tab helpers here unless they are intended for android too
  qorai_shields::QorAIShieldsTabHelper::CreateForWebContents(web_contents);
  ThumbnailTabHelper::CreateForWebContents(web_contents);
  QorAIGeolocationPermissionTabHelper::CreateForWebContents(web_contents);
#endif

#if BUILDFLAG(IS_WIN)
  if (base::FeatureList::IsEnabled(features::kQorAIWorkaroundNewWindowFlash)) {
    BackgroundColorTabHelper::CreateForWebContents(web_contents);
  }
#endif

  qorai_rewards::RewardsTabHelper::CreateForWebContents(web_contents);

  content::BrowserContext* context = web_contents->GetBrowserContext();
  if (ai_chat::IsAllowedForContext(context)) {
    ai_chat::AIChatTabHelper::CreateForWebContents(
        web_contents,
#if BUILDFLAG(ENABLE_PRINT_PREVIEW)
        std::make_unique<ai_chat::PrintPreviewExtractor>(
            web_contents,
            base::BindRepeating(
                [](content::WebContents* web_contents, bool is_pdf,
                   ai_chat::PrintPreviewExtractor::Extractor::ImageCallback&&
                       callback)
                    -> std::unique_ptr<
                        ai_chat::PrintPreviewExtractor::Extractor> {
                  return std::make_unique<
                      ai_chat::PrintPreviewExtractorInternal>(
                      web_contents,
                      Profile::FromBrowserContext(
                          web_contents->GetBrowserContext()),
                      is_pdf, std::move(callback),
                      base::BindRepeating(
                          []() -> base::IDMap<
                                   printing::mojom::PrintPreviewUI*>& {
                            return printing::PrintPreviewUI::
                                GetPrintPreviewUIIdMap();
                          }),
                      base::BindRepeating([]() -> base::flat_map<int, int>& {
                        return printing::PrintPreviewUI::
                            GetPrintPreviewUIRequestIdMap();
                      }));
                }))
#else
        nullptr
#endif
    );
  }

#if BUILDFLAG(ENABLE_WIDEVINE)
  QorAIDrmTabHelper::CreateForWebContents(web_contents);
#endif

#if BUILDFLAG(ENABLE_QORAI_WAYBACK_MACHINE)
  QorAIWaybackMachineTabHelper::CreateIfNeeded(web_contents);
#endif

  qorai_perf_predictor::PerfPredictorTabHelper::CreateForWebContents(
      web_contents);

  qorai_ads::AdsTabHelper::CreateForWebContents(web_contents);
  qorai_ads::CreativeSearchResultAdTabHelper::MaybeCreateForWebContents(
      web_contents);
#if BUILDFLAG(ENABLE_EXTENSIONS) || BUILDFLAG(ENABLE_WEB_DISCOVERY_NATIVE)
  web_discovery::WebDiscoveryTabHelper::MaybeCreateForWebContents(web_contents);
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
  speedreader::SpeedreaderTabHelper::MaybeCreateForWebContents(web_contents);
#endif

#if BUILDFLAG(ENABLE_TOR)
  tor::TorTabHelper::MaybeCreateForWebContents(web_contents);
  tor::OnionLocationTabHelper::CreateForWebContents(web_contents);
#endif

  QorAINewsTabHelper::MaybeCreateForWebContents(web_contents);

#if defined(TOOLKIT_VIEWS)
  OnboardingTabHelper::MaybeCreateForWebContents(web_contents);
  sidebar::SidebarTabHelper::MaybeCreateForWebContents(web_contents);
#endif

  qorai_wallet::QorAIWalletTabHelper::CreateForWebContents(web_contents);

  if (!web_contents->GetBrowserContext()->IsOffTheRecord()) {
    misc_metrics::PageMetricsTabHelper::CreateForWebContents(web_contents);
#if BUILDFLAG(ENABLE_REQUEST_OTR)
    if (base::FeatureList::IsEnabled(
            request_otr::features::kQorAIRequestOTRTab)) {
      RequestOTRTabHelper::CreateForWebContents(web_contents);
    }
#endif
  }

  if (base::FeatureList::IsEnabled(playlist::features::kPlaylist)) {
    if (auto* playlist_service =
            playlist::PlaylistServiceFactory::GetForBrowserContext(
                web_contents->GetBrowserContext())) {
      playlist::PlaylistTabHelper::CreateForWebContents(web_contents,
                                                        playlist_service);
    }
  }
}

void AttachPrivacySensitiveTabHelpers(content::WebContents* web_contents) {
  qorai_shields::QorAIShieldsWebContentsObserver::CreateForWebContents(
      web_contents);
  if (base::FeatureList::IsEnabled(net::features::kQorAIEphemeralStorage)) {
    ephemeral_storage::EphemeralStorageTabHelper::CreateForWebContents(
        web_contents);
  }
}

}  // namespace qorai
