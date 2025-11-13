// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_WEBUI_PRIVATE_NEW_TAB_PAGE_QORAI_PRIVATE_NEW_TAB_UI_H_
#define QORAI_BROWSER_UI_WEBUI_PRIVATE_NEW_TAB_PAGE_QORAI_PRIVATE_NEW_TAB_UI_H_

#include <memory>
#include <string>

#include "qorai/components/qorai_private_new_tab_ui/common/qorai_private_new_tab.mojom-forward.h"
#include "chrome/common/webui_url_constants.h"
#include "content/public/browser/web_ui_controller.h"
#include "content/public/browser/webui_config.h"
#include "content/public/common/url_constants.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "ui/webui/mojo_web_ui_controller.h"

class QoraiPrivateNewTabUI;

class QoraiPrivateNewTabUIConfig
    : public content::DefaultWebUIConfig<QoraiPrivateNewTabUI> {
 public:
  QoraiPrivateNewTabUIConfig()
      : DefaultWebUIConfig(content::kChromeUIScheme,
                           chrome::kChromeUINewTabHost) {}

  // content::WebUIConfig:
  bool IsWebUIEnabled(content::BrowserContext* browser_context) override;
};

class QoraiPrivateNewTabUI : public ui::MojoWebUIController {
 public:
  explicit QoraiPrivateNewTabUI(content::WebUI* web_ui);
  ~QoraiPrivateNewTabUI() override;
  QoraiPrivateNewTabUI(const QoraiPrivateNewTabUI&) = delete;
  QoraiPrivateNewTabUI& operator=(const QoraiPrivateNewTabUI&) = delete;

  void BindInterface(
      mojo::PendingReceiver<qorai_private_new_tab::mojom::PageHandler>
          receiver);

 private:
  std::unique_ptr<qorai_private_new_tab::mojom::PageHandler>
      private_tab_page_handler_;

  WEB_UI_CONTROLLER_TYPE_DECL();
};

#endif  // QORAI_BROWSER_UI_WEBUI_PRIVATE_NEW_TAB_PAGE_QORAI_PRIVATE_NEW_TAB_UI_H_
