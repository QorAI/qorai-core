// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/webui/qorai_new_tab_page_refresh/qorai_new_tab_page_ui.h"

#include <utility>

#include "qorai/browser/qorai_ads/ads_service_factory.h"
#include "qorai/browser/qorai_browser_process.h"
#include "qorai/browser/qorai_news/qorai_news_controller_factory.h"
#include "qorai/browser/qorai_rewards/rewards_service_factory.h"
#include "qorai/browser/misc_metrics/process_misc_metrics.h"
#include "qorai/browser/ntp_background/qorai_ntp_custom_background_service_factory.h"
#include "qorai/browser/ntp_background/custom_background_file_manager.h"
#include "qorai/browser/ntp_background/view_counter_service_factory.h"
#include "qorai/browser/ui/webui/qorai_new_tab_page_refresh/background_facade.h"
#include "qorai/browser/ui/webui/qorai_new_tab_page_refresh/custom_image_chooser.h"
#include "qorai/browser/ui/webui/qorai_new_tab_page_refresh/new_tab_page_handler.h"
#include "qorai/browser/ui/webui/qorai_new_tab_page_refresh/new_tab_page_initializer.h"
#include "qorai/browser/ui/webui/qorai_new_tab_page_refresh/top_sites_facade.h"
#include "qorai/browser/ui/webui/qorai_new_tab_page_refresh/vpn_facade.h"
#include "qorai/browser/ui/webui/qorai_rewards/rewards_page_handler.h"
#include "qorai/components/qorai_news/browser/qorai_news_controller.h"
#include "qorai/components/ntp_background_images/browser/ntp_sponsored_rich_media_ad_event_handler.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/ntp_tiles/chrome_most_visited_sites_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/search_engines/template_url_service_factory.h"
#include "chrome/browser/ui/webui/searchbox/realbox_handler.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/browser/qorai_vpn/qorai_vpn_service_factory.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service.h"
#endif

namespace {

using qorai_new_tab_page_refresh::BackgroundFacade;
using qorai_new_tab_page_refresh::CustomImageChooser;
using qorai_new_tab_page_refresh::NewTabPageHandler;
using qorai_new_tab_page_refresh::NewTabPageInitializer;
using qorai_new_tab_page_refresh::TopSitesFacade;
using qorai_new_tab_page_refresh::VPNFacade;

}  // namespace

QoraiNewTabPageUI::QoraiNewTabPageUI(content::WebUI* web_ui)
    : ui::MojoWebUIController(web_ui, /* enable_chrome_send = */ true) {
  NewTabPageInitializer(*web_ui).Initialize();
}

QoraiNewTabPageUI::~QoraiNewTabPageUI() = default;

void QoraiNewTabPageUI::BindInterface(
    mojo::PendingReceiver<qorai_new_tab_page_refresh::mojom::NewTabPageHandler>
        receiver) {
  auto* web_contents = web_ui()->GetWebContents();
  auto* profile = Profile::FromWebUI(web_ui());
  auto* prefs = profile->GetPrefs();
  auto image_chooser =
      std::make_unique<CustomImageChooser>(*web_contents, *profile);
  auto background_facade = std::make_unique<BackgroundFacade>(
      std::make_unique<CustomBackgroundFileManager>(profile), *prefs,
      g_qorai_browser_process->ntp_background_images_service(),
      ntp_background_images::ViewCounterServiceFactory::GetForProfile(profile));
  auto top_sites_facade = std::make_unique<TopSitesFacade>(
      ChromeMostVisitedSitesFactory::NewForProfile(profile), *prefs);

#if BUILDFLAG(ENABLE_QORAI_VPN)
  auto vpn_facade = std::make_unique<VPNFacade>(
      *web_contents, qorai_vpn::QoraiVpnServiceFactory::GetForProfile(profile));
#else
  auto vpn_facade = std::make_unique<VPNFacade>();
#endif

  page_handler_ = std::make_unique<NewTabPageHandler>(
      std::move(receiver), std::move(image_chooser),
      std::move(background_facade), std::move(top_sites_facade),
      std::move(vpn_facade), *web_contents, *prefs,
      *TemplateURLServiceFactory::GetForProfile(profile),
      *g_qorai_browser_process->process_misc_metrics()->new_tab_metrics());
}

void QoraiNewTabPageUI::BindInterface(
    mojo::PendingReceiver<
        ntp_background_images::mojom::SponsoredRichMediaAdEventHandler>
        receiver) {
  auto* profile = Profile::FromWebUI(web_ui());
  rich_media_ad_event_handler_ = std::make_unique<
      ntp_background_images::NTPSponsoredRichMediaAdEventHandler>(
      qorai_ads::AdsServiceFactory::GetForProfile(profile));
  rich_media_ad_event_handler_->Bind(std::move(receiver));
}

void QoraiNewTabPageUI::BindInterface(
    mojo::PendingReceiver<searchbox::mojom::PageHandler> receiver) {
  realbox_handler_ = std::make_unique<RealboxHandler>(
      std::move(receiver),
      /*composebox_metrics_recorder=*/nullptr, Profile::FromWebUI(web_ui()),
      web_ui()->GetWebContents());
}

void QoraiNewTabPageUI::BindInterface(
    mojo::PendingReceiver<qorai_rewards::mojom::RewardsPageHandler> receiver) {
  auto* profile = Profile::FromWebUI(web_ui());
  rewards_page_handler_ = std::make_unique<qorai_rewards::RewardsPageHandler>(
      std::move(receiver), nullptr,
      qorai_rewards::RewardsServiceFactory::GetForProfile(profile),
      qorai_ads::AdsServiceFactory::GetForProfile(profile), nullptr,
      profile->GetPrefs());
}

void QoraiNewTabPageUI::BindInterface(
    mojo::PendingReceiver<qorai_news::mojom::QoraiNewsController> receiver) {
  auto* profile = Profile::FromWebUI(web_ui());
  auto* qorai_news_controller =
      qorai_news::QoraiNewsControllerFactory::GetForBrowserContext(profile);
  if (qorai_news_controller) {
    qorai_news_controller->Bind(std::move(receiver));
  }
}

#if BUILDFLAG(ENABLE_QORAI_VPN)
void QoraiNewTabPageUI::BindInterface(
    mojo::PendingReceiver<qorai_vpn::mojom::ServiceHandler> receiver) {
  auto* vpn_service = qorai_vpn::QoraiVpnServiceFactory::GetForProfile(
      Profile::FromWebUI(web_ui()));
  if (vpn_service) {
    vpn_service->BindInterface(std::move(receiver));
  }
}
#endif

WEB_UI_CONTROLLER_TYPE_IMPL(QoraiNewTabPageUI)
