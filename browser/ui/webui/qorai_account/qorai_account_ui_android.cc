/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/qorai_account/qorai_account_ui_android.h"

#include <memory>

#include "base/check.h"
#include "base/functional/bind.h"
#include "base/values.h"
#include "qorai/components/qorai_account/features.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_ui.h"
#include "content/public/browser/web_ui_message_handler.h"
#include "content/public/common/url_constants.h"
#include "ui/webui/webui_util.h"

namespace {
class QoraiAccountUIMessageHandler : public content::WebUIMessageHandler {
 public:
  QoraiAccountUIMessageHandler() = default;

  QoraiAccountUIMessageHandler(const QoraiAccountUIMessageHandler&) = delete;
  QoraiAccountUIMessageHandler& operator=(const QoraiAccountUIMessageHandler&) =
      delete;

  ~QoraiAccountUIMessageHandler() override = default;

 private:
  // WebUIMessageHandler:
  void RegisterMessages() override;

  void OnDialogCloseMessage(const base::Value::List& args);
};

void QoraiAccountUIMessageHandler::RegisterMessages() {
  web_ui()->RegisterMessageCallback(
      "dialogClose",
      base::BindRepeating(&QoraiAccountUIMessageHandler::OnDialogCloseMessage,
                          base::Unretained(this)));
}

void QoraiAccountUIMessageHandler::OnDialogCloseMessage(
    const base::Value::List& args) {
  web_ui()->GetWebContents()->Close();
}
}  // namespace

QoraiAccountUIAndroid::QoraiAccountUIAndroid(content::WebUI* web_ui)
    : QoraiAccountUIBase(Profile::FromWebUI(web_ui),
                         base::BindOnce(&webui::SetupWebUIDataSource)),
      WebUIController(web_ui) {
  web_ui->AddMessageHandler(std::make_unique<QoraiAccountUIMessageHandler>());
}

WEB_UI_CONTROLLER_TYPE_IMPL(QoraiAccountUIAndroid)

QoraiAccountUIAndroidConfig::QoraiAccountUIAndroidConfig()
    : DefaultWebUIConfig(content::kChromeUIScheme, kQoraiAccountHost) {
  CHECK(qorai_account::features::IsQoraiAccountEnabled());
}
