// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_UI_WEBUI_QORAI_WEB_UI_CONTROLLER_FACTORY_H_
#define QORAI_IOS_BROWSER_UI_WEBUI_QORAI_WEB_UI_CONTROLLER_FACTORY_H_

#include <memory>

#import "ios/chrome/browser/webui/ui_bundled/chrome_web_ui_ios_controller_factory.h"
#import "ios/web/public/webui/web_ui_ios.h"
#import "ios/web/public/webui/web_ui_ios_controller.h"

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

class GURL;

class QoraiWebUIControllerFactory : public ChromeWebUIIOSControllerFactory {
 public:
  std::unique_ptr<web::WebUIIOSController> CreateWebUIIOSControllerForURL(
      web::WebUIIOS* web_ui,
      const GURL& url) const override;

  NSInteger GetErrorCodeForWebUIURL(const GURL& url) const override;

  static QoraiWebUIControllerFactory* GetInstance();

  QoraiWebUIControllerFactory(const QoraiWebUIControllerFactory&) = delete;
  QoraiWebUIControllerFactory& operator=(const QoraiWebUIControllerFactory&) =
      delete;

 protected:
  QoraiWebUIControllerFactory();
  ~QoraiWebUIControllerFactory() override;

 private:
  friend class base::NoDestructor<QoraiWebUIControllerFactory>;
};

#endif  // QORAI_IOS_BROWSER_UI_WEBUI_QORAI_WEB_UI_CONTROLLER_FACTORY_H_
