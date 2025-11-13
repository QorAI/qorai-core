// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/webui/qorai_new_tab_page_refresh/vpn_facade.h"

#include "base/types/to_address.h"
#include "qorai/components/constants/pref_names.h"
#include "chrome/browser/ui/browser_window/public/browser_window_features.h"
#include "chrome/browser/ui/browser_window/public/browser_window_interface.h"
#include "components/tabs/public/tab_interface.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/browser/ui/qorai_vpn/qorai_vpn_controller.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service.h"
#endif

namespace qorai_new_tab_page_refresh {

#if BUILDFLAG(ENABLE_QORAI_VPN)

VPNFacade::VPNFacade(content::WebContents& web_contents,
                     qorai_vpn::QoraiVpnService* vpn_service)
    : web_contents_(web_contents), vpn_service_(vpn_service) {}

VPNFacade::~VPNFacade() = default;

void VPNFacade::ReloadPurchasedState() {
  if (vpn_service_) {
    vpn_service_->ReloadPurchasedState();
  }
}

void VPNFacade::OpenPanel() {
  if (auto* controller = GetQoraiVPNController()) {
    controller->ShowQoraiVPNBubble(/* show_select */ true);
  }
}

void VPNFacade::OpenAccountPage(qorai_vpn::mojom::ManageURLType url_type) {
  if (auto* controller = GetQoraiVPNController()) {
    controller->OpenVPNAccountPage(url_type);
  }
}

void VPNFacade::RecordWidgetUsage() {
  if (vpn_service_) {
    vpn_service_->qorai_vpn_metrics()->RecordWidgetUsage(true);
  }
}

std::optional<std::string> VPNFacade::GetWidgetPrefName() {
  return kNewTabPageShowQoraiVPN;
}

QoraiVPNController* VPNFacade::GetQoraiVPNController() {
  if (auto* tab = tabs::TabInterface::MaybeGetFromContents(
          base::to_address(web_contents_))) {
    return tab->GetBrowserWindowInterface()
        ->GetFeatures()
        .qorai_vpn_controller();
  }

  return nullptr;
}

#endif

}  // namespace qorai_new_tab_page_refresh
