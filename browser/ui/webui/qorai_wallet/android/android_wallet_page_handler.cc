// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/webui/qorai_wallet/android/android_wallet_page_handler.h"

#include <utility>

#include "base/check.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_provider_delegate_impl_helper.h"

AndroidWalletPageHandler::AndroidWalletPageHandler(
    mojo::PendingReceiver<qorai_wallet::mojom::PageHandler> receiver,
    Profile* profile,
    ui::MojoWebUIController* webui_controller)
    : WalletPageHandler(std::move(receiver), profile),
      webui_controller_(webui_controller) {
  DCHECK(webui_controller_);
}
AndroidWalletPageHandler::~AndroidWalletPageHandler() = default;

void AndroidWalletPageHandler::ShowApprovePanelUI() {
  if (!webui_controller_) {
    return;
  }

  ::qorai_wallet::ShowPanel(webui_controller_->web_ui()->GetWebContents());
}

void AndroidWalletPageHandler::ShowWalletBackupUI() {
  ::qorai_wallet::ShowWalletBackup();
}

void AndroidWalletPageHandler::UnlockWalletUI() {
  ::qorai_wallet::UnlockWallet();
}
