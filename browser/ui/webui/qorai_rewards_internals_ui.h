/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_REWARDS_INTERNALS_UI_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_REWARDS_INTERNALS_UI_H_

#include <string>

#include "content/public/browser/web_ui_controller.h"

class QoraiRewardsInternalsUI : public content::WebUIController {
 public:
  QoraiRewardsInternalsUI(content::WebUI* web_ui, const std::string& host);
  ~QoraiRewardsInternalsUI() override;
  QoraiRewardsInternalsUI(const QoraiRewardsInternalsUI&) = delete;
  QoraiRewardsInternalsUI& operator=(const QoraiRewardsInternalsUI&) = delete;
};

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_REWARDS_INTERNALS_UI_H_
