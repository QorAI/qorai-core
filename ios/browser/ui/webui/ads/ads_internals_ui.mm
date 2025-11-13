// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/ios/browser/ui/webui/ads/ads_internals_ui.h"

#include <cstddef>
#include <string>
#include <utility>

#include "base/check.h"
#include "base/containers/span.h"
#include "base/functional/bind.h"
#include "qorai/components/qorai_ads/browser/resources/grit/ads_internals_generated_map.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "qorai/ios/browser/qorai_ads/ads_service_factory_ios.h"
#include "qorai/ios/browser/qorai_ads/ads_service_impl_ios.h"
#include "qorai/ios/web/webui/qorai_webui_utils.h"
#include "components/grit/qorai_components_resources.h"
#include "components/prefs/pref_service.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"
#include "ios/web/public/web_state.h"
#include "ios/web/public/webui/web_ui_ios.h"
#include "ios/web/public/webui/web_ui_ios_data_source.h"
#include "ui/base/webui/resource_path.h"

AdsInternalsUI::AdsInternalsUI(web::WebUIIOS* web_ui, const GURL& url)
    : web::WebUIIOSController(web_ui, url.host()),
      handler_(qorai_ads::AdsServiceFactoryIOS::GetForProfile(
                   ProfileIOS::FromWebUIIOS(web_ui)),
               *ProfileIOS::FromWebUIIOS(web_ui)->GetPrefs()) {
  qorai::CreateAndAddWebUIDataSource(web_ui, url.host(),
                                     base::span(kAdsInternalsGenerated),
                                     IDR_ADS_INTERNALS_HTML);

  // Bind Mojom Interface
  web_ui->GetWebState()->GetInterfaceBinderForMainFrame()->AddInterface(
      base::BindRepeating(&AdsInternalsUI::BindInterface,
                          weak_ptr_factory_.GetWeakPtr()));
}

AdsInternalsUI::~AdsInternalsUI() {
  web_ui()->GetWebState()->GetInterfaceBinderForMainFrame()->RemoveInterface(
      bat_ads::mojom::AdsInternals::Name_);
}

void AdsInternalsUI::BindInterface(
    mojo::PendingReceiver<bat_ads::mojom::AdsInternals> pending_receiver) {
  handler_.BindInterface(std::move(pending_receiver));
}
