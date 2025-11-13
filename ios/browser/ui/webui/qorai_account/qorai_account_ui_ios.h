/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_UI_WEBUI_QORAI_ACCOUNT_QORAI_ACCOUNT_UI_IOS_H_
#define QORAI_IOS_BROWSER_UI_WEBUI_QORAI_ACCOUNT_QORAI_ACCOUNT_UI_IOS_H_

#include "qorai/components/qorai_account/qorai_account_ui_base.h"
#include "qorai/ios/browser/qorai_account/qorai_account_service_factory_ios.h"
#include "qorai/ios/web/webui/qorai_web_ui_ios_data_source.h"
#include "ios/web/public/webui/web_ui_ios_controller.h"

class GURL;

namespace web {
class WebUIIOS;
}

class QoraiAccountUIIOS
    : public QoraiAccountUIBase<QoraiWebUIIOSDataSource,
                                qorai_account::QoraiAccountServiceFactoryIOS>,
      public web::WebUIIOSController {
 public:
  QoraiAccountUIIOS(web::WebUIIOS* web_ui, const GURL& url);

  ~QoraiAccountUIIOS() override;
};

#endif  // QORAI_IOS_BROWSER_UI_WEBUI_QORAI_ACCOUNT_QORAI_ACCOUNT_UI_IOS_H_
