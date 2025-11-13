// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_UI_WEBUI_QORAI_WALLET_LINE_CHART_UI_H_
#define QORAI_IOS_BROWSER_UI_WEBUI_QORAI_WALLET_LINE_CHART_UI_H_

#include "ios/web/public/webui/web_ui_ios.h"
#include "ios/web/public/webui/web_ui_ios_controller.h"
#include "url/gurl.h"

namespace line_chart {

class UntrustedLineChartUI : public web::WebUIIOSController {
 public:
  explicit UntrustedLineChartUI(web::WebUIIOS* web_ui, const GURL& url);
  UntrustedLineChartUI(const UntrustedLineChartUI&) = delete;
  UntrustedLineChartUI& operator=(const UntrustedLineChartUI&) = delete;
  ~UntrustedLineChartUI() override;
};

}  // namespace line_chart

#endif  // QORAI_IOS_BROWSER_UI_WEBUI_QORAI_WALLET_LINE_CHART_UI_H_
