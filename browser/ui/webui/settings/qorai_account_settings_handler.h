/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_ACCOUNT_SETTINGS_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_ACCOUNT_SETTINGS_HANDLER_H_

#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_account/mojom/qorai_account_settings_handler.mojom.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/receiver.h"

namespace content {
class WebUI;
}  // namespace content

namespace qorai_account {
class QoraiAccountSettingsHandler : public mojom::QoraiAccountSettingsHandler {
 public:
  explicit QoraiAccountSettingsHandler(
      mojo::PendingReceiver<mojom::QoraiAccountSettingsHandler> handler,
      content::WebUI* web_ui);

  QoraiAccountSettingsHandler(const QoraiAccountSettingsHandler&) = delete;
  QoraiAccountSettingsHandler& operator=(const QoraiAccountSettingsHandler&) =
      delete;

  ~QoraiAccountSettingsHandler() override;

  void OpenDialog() override;

 private:
  mojo::Receiver<mojom::QoraiAccountSettingsHandler> handler_;
  raw_ptr<content::WebUI> web_ui_;
};
}  // namespace qorai_account

#endif  // QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_ACCOUNT_SETTINGS_HANDLER_H_
