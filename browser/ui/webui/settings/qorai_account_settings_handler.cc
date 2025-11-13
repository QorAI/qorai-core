/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/settings/qorai_account_settings_handler.h"

#include <utility>

#include "qorai/browser/ui/webui/qorai_account/qorai_account_ui_desktop.h"

namespace qorai_account {
QoraiAccountSettingsHandler::QoraiAccountSettingsHandler(
    mojo::PendingReceiver<mojom::QoraiAccountSettingsHandler> handler,
    content::WebUI* web_ui)
    : handler_(this, std::move(handler)), web_ui_(web_ui) {}

QoraiAccountSettingsHandler::~QoraiAccountSettingsHandler() = default;

void QoraiAccountSettingsHandler::OpenDialog() {
  ShowQoraiAccountDialog(web_ui_);
}
}  // namespace qorai_account
