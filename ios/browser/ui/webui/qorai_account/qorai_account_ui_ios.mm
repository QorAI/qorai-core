/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/ios/browser/ui/webui/qorai_account/qorai_account_ui_ios.h"

#include <memory>

#include "base/functional/bind.h"
#include "base/values.h"
#include "qorai/components/qorai_account/mojom/qorai_account.mojom.h"
#include "qorai/components/password_strength_meter/password_strength_meter.mojom.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"
#include "ios/web/public/web_state.h"
#include "ios/web/public/webui/web_ui_ios.h"
#include "ios/web/public/webui/web_ui_ios_message_handler.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "url/gurl.h"

namespace {

class QoraiAccountUIMessageHandler : public web::WebUIIOSMessageHandler {
 public:
  QoraiAccountUIMessageHandler() = default;

  QoraiAccountUIMessageHandler(const QoraiAccountUIMessageHandler&) = delete;
  QoraiAccountUIMessageHandler& operator=(const QoraiAccountUIMessageHandler&) =
      delete;

  ~QoraiAccountUIMessageHandler() override = default;

 private:
  // WebUIIOSMessageHandler:
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
  web_ui()->GetWebState()->CloseWebState();
}

}  // namespace

QoraiAccountUIIOS::QoraiAccountUIIOS(web::WebUIIOS* web_ui, const GURL& url)
    : QoraiAccountUIBase(ProfileIOS::FromWebUIIOS(web_ui)),
      web::WebUIIOSController(web_ui, url.host()) {
  using Authentication = void (QoraiAccountUIBase::*)(
      mojo::PendingReceiver<qorai_account::mojom::Authentication>);
  web_ui->GetWebState()->GetInterfaceBinderForMainFrame()->AddInterface(
      base::BindRepeating(
          static_cast<Authentication>(&QoraiAccountUIBase::BindInterface),
          base::Unretained(this)));

  using PasswordStrengthMeter = void (QoraiAccountUIBase::*)(
      mojo::PendingReceiver<
          password_strength_meter::mojom::PasswordStrengthMeter>);
  web_ui->GetWebState()->GetInterfaceBinderForMainFrame()->AddInterface(
      base::BindRepeating(static_cast<PasswordStrengthMeter>(
                              &QoraiAccountUIBase::BindInterface),
                          base::Unretained(this)));

  web_ui->AddMessageHandler(std::make_unique<QoraiAccountUIMessageHandler>());
}

QoraiAccountUIIOS::~QoraiAccountUIIOS() {
  web_ui()->GetWebState()->GetInterfaceBinderForMainFrame()->RemoveInterface(
      qorai_account::mojom::Authentication::Name_);

  web_ui()->GetWebState()->GetInterfaceBinderForMainFrame()->RemoveInterface(
      password_strength_meter::mojom::PasswordStrengthMeter::Name_);
}
