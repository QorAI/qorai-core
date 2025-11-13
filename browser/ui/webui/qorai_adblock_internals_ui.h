// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_ADBLOCK_INTERNALS_UI_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_ADBLOCK_INTERNALS_UI_H_

#include "qorai/components/constants/webui_url_constants.h"
#include "content/public/browser/web_ui_controller.h"
#include "content/public/browser/webui_config.h"
#include "content/public/common/url_constants.h"

class QoraiAdblockInternalsUI;

class QoraiAdblockInternalsUIConfig
    : public content::DefaultWebUIConfig<QoraiAdblockInternalsUI> {
 public:
  QoraiAdblockInternalsUIConfig()
      : DefaultWebUIConfig(content::kChromeUIScheme, kAdblockInternalsHost) {}
};

// The WebUI for qorai://adblock-internals
class QoraiAdblockInternalsUI : public content::WebUIController {
 public:
  explicit QoraiAdblockInternalsUI(content::WebUI* web_ui);

  QoraiAdblockInternalsUI(const QoraiAdblockInternalsUI&) = delete;
  QoraiAdblockInternalsUI& operator=(const QoraiAdblockInternalsUI&) = delete;

  ~QoraiAdblockInternalsUI() override;
};

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_ADBLOCK_INTERNALS_UI_H_
