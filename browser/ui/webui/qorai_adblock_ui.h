/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_ADBLOCK_UI_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_ADBLOCK_UI_H_

#include "qorai/components/constants/webui_url_constants.h"
#include "content/public/browser/web_ui_controller.h"
#include "content/public/browser/webui_config.h"
#include "content/public/common/url_constants.h"

class QoraiAdblockUI;

class QoraiAdblockUIConfig
    : public content::DefaultWebUIConfig<QoraiAdblockUI> {
 public:
  QoraiAdblockUIConfig()
      : DefaultWebUIConfig(content::kChromeUIScheme, kAdblockHost) {}
};

class QoraiAdblockUI : public content::WebUIController {
 public:
  explicit QoraiAdblockUI(content::WebUI* web_ui);
  ~QoraiAdblockUI() override;
  QoraiAdblockUI(const QoraiAdblockUI&) = delete;
  QoraiAdblockUI& operator=(const QoraiAdblockUI&) = delete;
};

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_ADBLOCK_UI_H_
