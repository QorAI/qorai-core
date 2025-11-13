// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_NEW_TAB_PAGE_REFRESH_QORAI_NEW_TAB_PAGE_UI_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_NEW_TAB_PAGE_REFRESH_QORAI_NEW_TAB_PAGE_UI_H_

#include <memory>

#include "qorai/browser/ui/webui/qorai_new_tab_page_refresh/qorai_new_tab_page.mojom.h"
#include "qorai/components/qorai_news/common/qorai_news.mojom-forward.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards_page.mojom.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/ntp_background_images/browser/mojom/ntp_background_images.mojom.h"
#include "components/omnibox/browser/searchbox.mojom.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "ui/webui/mojo_web_ui_controller.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/components/qorai_vpn/common/mojom/qorai_vpn.mojom.h"
#endif

namespace ntp_background_images {
class NTPSponsoredRichMediaAdEventHandler;
}

namespace qorai_rewards {
class RewardsPageHandler;
}

class RealboxHandler;

// The Web UI controller for the Qorai new tab page.
class QoraiNewTabPageUI : public ui::MojoWebUIController {
 public:
  explicit QoraiNewTabPageUI(content::WebUI* web_ui);
  ~QoraiNewTabPageUI() override;

  void BindInterface(
      mojo::PendingReceiver<
          qorai_new_tab_page_refresh::mojom::NewTabPageHandler> receiver);

  void BindInterface(
      mojo::PendingReceiver<
          ntp_background_images::mojom::SponsoredRichMediaAdEventHandler>
          receiver);

  void BindInterface(
      mojo::PendingReceiver<searchbox::mojom::PageHandler> receiver);

  void BindInterface(
      mojo::PendingReceiver<qorai_rewards::mojom::RewardsPageHandler> receiver);

  void BindInterface(
      mojo::PendingReceiver<qorai_news::mojom::QoraiNewsController> receiver);

#if BUILDFLAG(ENABLE_QORAI_VPN)
  void BindInterface(
      mojo::PendingReceiver<qorai_vpn::mojom::ServiceHandler> receiver);
#endif

 private:
  std::unique_ptr<qorai_new_tab_page_refresh::mojom::NewTabPageHandler>
      page_handler_;
  std::unique_ptr<ntp_background_images::NTPSponsoredRichMediaAdEventHandler>
      rich_media_ad_event_handler_;
  std::unique_ptr<RealboxHandler> realbox_handler_;
  std::unique_ptr<qorai_rewards::RewardsPageHandler> rewards_page_handler_;

  WEB_UI_CONTROLLER_TYPE_DECL();
};

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_NEW_TAB_PAGE_REFRESH_QORAI_NEW_TAB_PAGE_UI_H_
