// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_VPN_VPN_PANEL_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_VPN_VPN_PANEL_HANDLER_H_

#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_vpn/common/mojom/qorai_vpn.mojom.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/webui/top_chrome/top_chrome_web_ui_controller.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/receiver.h"

namespace content {
class WebUI;
}  // namespace content

class VPNPanelUI;

class VPNPanelHandler : public qorai_vpn::mojom::PanelHandler {
 public:
  using GetWebContentsForTabCallback =
      base::RepeatingCallback<content::WebContents*(int32_t)>;

  VPNPanelHandler(
      mojo::PendingReceiver<qorai_vpn::mojom::PanelHandler> receiver,
      VPNPanelUI* panel_controller,
      Profile* profile);

  VPNPanelHandler(const VPNPanelHandler&) = delete;
  VPNPanelHandler& operator=(const VPNPanelHandler&) = delete;
  ~VPNPanelHandler() override;

  // qorai_vpn::mojom::PanelHandler:
  void ShowUI() override;
  void CloseUI() override;
  void OpenVpnUI(qorai_vpn::mojom::ManageURLType type) override;

 private:
  void OpenVpnUIUrl(qorai_vpn::mojom::ManageURLType type,
                    qorai_vpn::mojom::ProductUrlsPtr product_urls);
  mojo::Receiver<qorai_vpn::mojom::PanelHandler> receiver_;
  raw_ptr<VPNPanelUI> const panel_controller_;
  raw_ptr<Profile> profile_;
};

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_VPN_VPN_PANEL_HANDLER_H_
