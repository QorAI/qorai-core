// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_WEBUI_ADS_INTERNALS_ADS_INTERNALS_UI_H_
#define QORAI_BROWSER_UI_WEBUI_ADS_INTERNALS_ADS_INTERNALS_UI_H_

#include <string>

#include "qorai/components/qorai_ads/core/browser/internals/ads_internals_handler.h"
#include "qorai/components/services/bat_ads/public/interfaces/bat_ads.mojom.h"
#include "components/prefs/pref_change_registrar.h"
#include "content/public/browser/web_ui_controller.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"

class PrefService;

namespace qorai_ads {
class AdsService;
}  // namespace qorai_ads

class AdsInternalsUI : public content::WebUIController {
 public:
  AdsInternalsUI(content::WebUI* const web_ui,
                 const std::string& name,
                 qorai_ads::AdsService* ads_service,
                 PrefService& prefs);

  AdsInternalsUI(const AdsInternalsUI&) = delete;
  AdsInternalsUI& operator=(const AdsInternalsUI&) = delete;

  ~AdsInternalsUI() override;

  void BindInterface(
      mojo::PendingReceiver<bat_ads::mojom::AdsInternals> pending_receiver);

 private:
  AdsInternalsHandler handler_;

  WEB_UI_CONTROLLER_TYPE_DECL();
};

#endif  // QORAI_BROWSER_UI_WEBUI_ADS_INTERNALS_ADS_INTERNALS_UI_H_
