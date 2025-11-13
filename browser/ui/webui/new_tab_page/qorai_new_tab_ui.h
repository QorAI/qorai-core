// Copyright (c) 2019 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_WEBUI_NEW_TAB_PAGE_QORAI_NEW_TAB_UI_H_
#define QORAI_BROWSER_UI_WEBUI_NEW_TAB_PAGE_QORAI_NEW_TAB_UI_H_

#include <memory>
#include <string>

#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_new_tab_ui/qorai_new_tab_page.mojom.h"
#include "qorai/components/qorai_news/common/qorai_news.mojom.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "chrome/browser/ui/webui/searchbox/realbox_handler.h"
#include "components/omnibox/browser/searchbox.mojom.h"
#include "components/regional_capabilities/regional_capabilities_service.h"
#include "content/public/browser/web_ui_controller.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "ui/webui/mojo_web_ui_controller.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/components/qorai_vpn/common/mojom/qorai_vpn.mojom.h"  // nogncheck
#endif  // BUILDFLAG(ENABLE_QORAI_VPN)

namespace qorai_ads {
class AdsService;
}  // namespace qorai_ads

namespace ntp_background_images {
class NTPSponsoredRichMediaAdEventHandler;
class ViewCounterService;
}  // namespace ntp_background_images

class QoraiNewTabPageHandler;

class QoraiNewTabUI : public ui::MojoWebUIController,
                      public qorai_new_tab_page::mojom::PageHandlerFactory {
 public:
  QoraiNewTabUI(content::WebUI* web_ui,
                const std::string& name,
                qorai_ads::AdsService* ads_service,
                ntp_background_images::ViewCounterService* view_counter_service,
                regional_capabilities::RegionalCapabilitiesService*
                    regional_capabilities);
  ~QoraiNewTabUI() override;
  QoraiNewTabUI(const QoraiNewTabUI&) = delete;
  QoraiNewTabUI& operator=(const QoraiNewTabUI&) = delete;

  // Instantiates the implementor of the mojo
  // interface passing the pending receiver that will be internally bound.
  void BindInterface(
      mojo::PendingReceiver<qorai_news::mojom::QoraiNewsController> receiver);

  void BindInterface(
      mojo::PendingReceiver<qorai_new_tab_page::mojom::PageHandlerFactory>
          pending_receiver);

  void BindInterface(mojo::PendingReceiver<searchbox::mojom::PageHandler>
                         pending_page_handler);

#if BUILDFLAG(ENABLE_QORAI_VPN)
  void BindInterface(mojo::PendingReceiver<qorai_vpn::mojom::ServiceHandler>
                         pending_vpn_service_handler);
#endif

 private:
  // new_tab_page::mojom::PageHandlerFactory:
  void CreatePageHandler(
      mojo::PendingRemote<qorai_new_tab_page::mojom::Page> pending_page,
      mojo::PendingReceiver<qorai_new_tab_page::mojom::PageHandler>
          pending_page_handler,
      mojo::PendingReceiver<qorai_new_tab_page::mojom::NewTabMetrics>
          pending_new_tab_metrics,
      mojo::PendingReceiver<
          ntp_background_images::mojom::SponsoredRichMediaAdEventHandler>
          pending_rich_media_ad_event_handler) override;

  std::unique_ptr<QoraiNewTabPageHandler> page_handler_;
  std::unique_ptr<RealboxHandler> realbox_handler_;
  mojo::Receiver<qorai_new_tab_page::mojom::PageHandlerFactory>
      page_factory_receiver_;
  std::unique_ptr<ntp_background_images::NTPSponsoredRichMediaAdEventHandler>
      rich_media_ad_event_handler_;
  raw_ptr<regional_capabilities::RegionalCapabilitiesService>
      regional_capabilities_ = nullptr;

  WEB_UI_CONTROLLER_TYPE_DECL();
};

#endif  // QORAI_BROWSER_UI_WEBUI_NEW_TAB_PAGE_QORAI_NEW_TAB_UI_H_
