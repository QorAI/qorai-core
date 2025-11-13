/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_WELCOME_PAGE_QORAI_WELCOME_UI_H_
#define QORAI_BROWSER_UI_WEBUI_WELCOME_PAGE_QORAI_WELCOME_UI_H_

#include <string>

#include "content/public/browser/web_ui_controller.h"

class QoraiWelcomeUI : public content::WebUIController {
 public:
  QoraiWelcomeUI(content::WebUI* web_ui, const std::string& host);
  ~QoraiWelcomeUI() override;
  QoraiWelcomeUI(const QoraiWelcomeUI&) = delete;
  QoraiWelcomeUI& operator=(const QoraiWelcomeUI&) = delete;
};

#endif  // QORAI_BROWSER_UI_WEBUI_WELCOME_PAGE_QORAI_WELCOME_UI_H_
