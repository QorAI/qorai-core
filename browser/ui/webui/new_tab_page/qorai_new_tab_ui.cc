// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/webui/new_tab_page/qorai_new_tab_ui.h"

#include <utility>

#include "base/check.h"
#include "base/check_is_test.h"
#include "base/feature_list.h"
#include "qorai/browser/qorai_browser_process.h"
#include "qorai/browser/qorai_news/qorai_news_controller_factory.h"
#include "qorai/browser/misc_metrics/process_misc_metrics.h"
#include "qorai/browser/new_tab/new_tab_shows_options.h"
#include "qorai/browser/ntp_background/qorai_ntp_custom_background_service_factory.h"
#include "qorai/browser/ui/qorai_ui_features.h"
#include "qorai/browser/ui/webui/qorai_new_tab_page_refresh/new_tab_page_initializer.h"
#include "qorai/browser/ui/webui/qorai_sanitized_image_source.h"
#include "qorai/browser/ui/webui/qorai_webui_source.h"
#include "qorai/browser/ui/webui/new_tab_page/qorai_new_tab_message_handler.h"
#include "qorai/browser/ui/webui/new_tab_page/qorai_new_tab_page_handler.h"
#include "qorai/browser/ui/webui/new_tab_page/top_sites_message_handler.h"
#include "qorai/components/qorai_ads/core/browser/service/ads_service.h"
#include "qorai/components/qorai_new_tab/resources/grit/qorai_new_tab_generated_map.h"
#include "qorai/components/qorai_news/browser/qorai_news_controller.h"
#include "qorai/components/qorai_news/common/features.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "qorai/components/misc_metrics/new_tab_metrics.h"
#include "qorai/components/ntp_background_images/browser/ntp_custom_images_source.h"
#include "qorai/components/ntp_background_images/browser/ntp_sponsored_rich_media_ad_event_handler.h"
#include "qorai/components/ntp_background_images/browser/view_counter_service.h"
#include "qorai/components/ntp_background_images/common/url_constants.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/search_engines/template_url_service_factory.h"
#include "chrome/browser/themes/theme_syncable_service.h"
#include "chrome/browser/ui/webui/theme_source.h"
#include "chrome/common/pref_names.h"
#include "components/country_codes/country_codes.h"
#include "components/grit/qorai_components_resources.h"
#include "components/grit/qorai_components_webui_strings.h"
#include "components/omnibox/browser/searchbox.mojom.h"
#include "components/prefs/pref_service.h"
#include "components/strings/grit/components_strings.h"
#include "content/public/browser/navigation_controller.h"
#include "content/public/browser/navigation_entry.h"
#include "content/public/browser/url_data_source.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_ui_data_source.h"
#include "content/public/common/url_constants.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "third_party/abseil-cpp/absl/strings/str_format.h"
#include "ui/base/l10n/l10n_util.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/browser/qorai_vpn/qorai_vpn_service_factory.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#endif

using ntp_background_images::NTPCustomImagesSource;

QoraiNewTabUI::QoraiNewTabUI(
    content::WebUI* web_ui,
    const std::string& name,
    qorai_ads::AdsService* ads_service,
    ntp_background_images::ViewCounterService* view_counter_service,
    regional_capabilities::RegionalCapabilitiesService* regional_capabilities)
    : ui::MojoWebUIController(
          web_ui,
          true /* Needed for legacy non-mojom message handler */),
      page_factory_receiver_(this),
      regional_capabilities_(regional_capabilities) {
  content::WebContents* web_contents = web_ui->GetWebContents();
  CHECK(web_contents);

  content::NavigationEntry* navigation_entry =
      web_contents->GetController().GetLastCommittedEntry();
  const bool was_restored = navigation_entry && navigation_entry->IsRestored();

  Profile* profile = Profile::FromWebUI(web_ui);
  web_ui->OverrideTitle(l10n_util::GetStringUTF16(IDS_NEW_TAB_TITLE));

  if (qorai::ShouldNewTabShowBlankpage(profile)) {
    content::WebUIDataSource* source =
        content::WebUIDataSource::CreateAndAdd(profile, name);
    source->SetDefaultResource(IDR_QORAI_BLANK_NEW_TAB_HTML);
    AddBackgroundColorToSource(source, web_contents);
    return;
  }

  // Non blank NTP.
  content::WebUIDataSource* source = CreateAndAddWebUIDataSource(
      web_ui, name, kQoraiNewTabGenerated, IDR_QORAI_NEW_TAB_HTML);

  web_ui->AddRequestableScheme(content::kChromeUIUntrustedScheme);

  AddBackgroundColorToSource(source, web_contents);

  // Lottie animations tick on a worker thread and requires the document CSP to
  // be set to "worker-src blob: 'self';".
  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::WorkerSrc,
      "worker-src blob: chrome://resources 'self';");

  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::TrustedTypes,
      "trusted-types static-types lottie-worker-script-loader lit-html-desktop "
      "default; ");

  source->AddBoolean("featureCustomBackgroundEnabled",
                     !profile->GetPrefs()->IsManagedPreference(
                         prefs::kNtpCustomBackgroundDict));

  // Let frontend know about feature flags
  source->AddBoolean("featureFlagQoraiNewsPromptEnabled",
                     base::FeatureList::IsEnabled(
                         qorai_news::features::kQoraiNewsCardPeekFeature));

  source->AddBoolean(
      "featureFlagQoraiNewsFeedV2Enabled",
      base::FeatureList::IsEnabled(qorai_news::features::kQoraiNewsFeedUpdate));

  source->AddBoolean(
      "featureFlagSearchWidget",
      base::FeatureList::IsEnabled(features::kQoraiNtpSearchWidget));
  source->AddString(
      "searchWidgetDefaultHost",
      qorai_new_tab_page_refresh::GetSearchDefaultHost(regional_capabilities_));

  source->AddString("newTabTakeoverLearnMoreLinkUrl",
                    ntp_background_images::kNewTabTakeoverLearnMoreLinkUrl);

  source->AddBoolean("vpnWidgetSupported",
#if BUILDFLAG(ENABLE_QORAI_VPN)
                     qorai_vpn::IsQoraiVPNEnabled(profile->GetPrefs())
#else
                     false
#endif
  );

  web_ui->AddMessageHandler(base::WrapUnique(
      QoraiNewTabMessageHandler::Create(source, profile, was_restored)));
  web_ui->AddMessageHandler(std::make_unique<TopSitesMessageHandler>(profile));

  // For custom background images.
  if (auto* ntp_custom_background_images_service =
          QoraiNTPCustomBackgroundServiceFactory::GetForContext(profile)) {
    content::URLDataSource::Add(profile,
                                std::make_unique<NTPCustomImagesSource>(
                                    ntp_custom_background_images_service));
  }

  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::FrameSrc,
      absl::StrFormat("frame-src %s;", kNTPNewTabTakeoverRichMediaUrl));
  source->AddString("ntpNewTabTakeoverRichMediaUrl",
                    kNTPNewTabTakeoverRichMediaUrl);

  rich_media_ad_event_handler_ = std::make_unique<
      ntp_background_images::NTPSponsoredRichMediaAdEventHandler>(ads_service);

  source->AddLocalizedStrings(webui::kQoraiNewsStrings);

  // Add a SanitizedImageSource to allow fetching images for Qorai News.
  content::URLDataSource::Add(
      profile, std::make_unique<QoraiSanitizedImageSource>(profile));

  content::URLDataSource::Add(profile, std::make_unique<ThemeSource>(profile));
}

QoraiNewTabUI::~QoraiNewTabUI() = default;

void QoraiNewTabUI::BindInterface(
    mojo::PendingReceiver<qorai_news::mojom::QoraiNewsController> receiver) {
  auto* profile = Profile::FromWebUI(web_ui());
  CHECK(profile);
  // Wire up JS mojom to service
  auto* qorai_news_controller =
      qorai_news::QoraiNewsControllerFactory::GetForBrowserContext(profile);
  if (qorai_news_controller) {
    qorai_news_controller->Bind(std::move(receiver));
  }
}

void QoraiNewTabUI::BindInterface(
    mojo::PendingReceiver<qorai_new_tab_page::mojom::PageHandlerFactory>
        pending_receiver) {
  if (page_factory_receiver_.is_bound()) {
    page_factory_receiver_.reset();
  }

  page_factory_receiver_.Bind(std::move(pending_receiver));
}

void QoraiNewTabUI::BindInterface(
    mojo::PendingReceiver<searchbox::mojom::PageHandler> pending_page_handler) {
  auto* profile = Profile::FromWebUI(web_ui());
  CHECK(profile);

  realbox_handler_ =
      std::make_unique<RealboxHandler>(std::move(pending_page_handler),
                                       /*composebox_metrics_recorder=*/nullptr,
                                       profile, web_ui()->GetWebContents());
}

#if BUILDFLAG(ENABLE_QORAI_VPN)
void QoraiNewTabUI::BindInterface(
    mojo::PendingReceiver<qorai_vpn::mojom::ServiceHandler>
        pending_vpn_service_handler) {
  auto* profile = Profile::FromWebUI(web_ui());
  CHECK(profile);
  auto* vpn_service = qorai_vpn::QoraiVpnServiceFactory::GetForProfile(profile);
  if (vpn_service) {
    vpn_service->BindInterface(std::move(pending_vpn_service_handler));
  }
}
#endif

void QoraiNewTabUI::CreatePageHandler(
    mojo::PendingRemote<qorai_new_tab_page::mojom::Page> pending_page,
    mojo::PendingReceiver<qorai_new_tab_page::mojom::PageHandler>
        pending_page_handler,
    mojo::PendingReceiver<qorai_new_tab_page::mojom::NewTabMetrics>
        pending_new_tab_metrics,
    mojo::PendingReceiver<
        ntp_background_images::mojom::SponsoredRichMediaAdEventHandler>
        pending_rich_media_ad_event_handler) {
  DCHECK(pending_page.is_valid());
  Profile* profile = Profile::FromWebUI(web_ui());
  page_handler_ = std::make_unique<QoraiNewTabPageHandler>(
      std::move(pending_page_handler), std::move(pending_page), profile,
      web_ui()->GetWebContents());
  g_qorai_browser_process->process_misc_metrics()->new_tab_metrics()->Bind(
      std::move(pending_new_tab_metrics));
  rich_media_ad_event_handler_->Bind(
      std::move(pending_rich_media_ad_event_handler));
}

WEB_UI_CONTROLLER_TYPE_IMPL(QoraiNewTabUI)
