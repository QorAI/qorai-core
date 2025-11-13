/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_ACCOUNT_QORAI_ACCOUNT_UI_ANDROID_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_ACCOUNT_QORAI_ACCOUNT_UI_ANDROID_H_

#include "qorai/browser/qorai_account/qorai_account_service_factory.h"
#include "qorai/components/qorai_account/qorai_account_ui_base.h"
#include "content/public/browser/web_ui_controller.h"
#include "content/public/browser/web_ui_data_source.h"
#include "content/public/browser/webui_config.h"

namespace content {
class WebUI;
}  // namespace content

class QoraiAccountUIAndroid
    : public QoraiAccountUIBase<content::WebUIDataSource,
                                qorai_account::QoraiAccountServiceFactory>,
      public content::WebUIController {
 public:
  explicit QoraiAccountUIAndroid(content::WebUI* web_ui);

 private:
  WEB_UI_CONTROLLER_TYPE_DECL();
};

class QoraiAccountUIAndroidConfig
    : public content::DefaultWebUIConfig<QoraiAccountUIAndroid> {
 public:
  QoraiAccountUIAndroidConfig();
};

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_ACCOUNT_QORAI_ACCOUNT_UI_ANDROID_H_
