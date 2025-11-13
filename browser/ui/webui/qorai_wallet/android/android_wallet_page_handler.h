// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_WALLET_ANDROID_ANDROID_WALLET_PAGE_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_WALLET_ANDROID_ANDROID_WALLET_PAGE_HANDLER_H_

#include "base/memory/raw_ptr.h"
#include "qorai/browser/ui/webui/qorai_wallet/page_handler/wallet_page_handler.h"

#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "ui/webui/mojo_web_ui_controller.h"

class AndroidWalletPageHandler : WalletPageHandler {
 public:
  AndroidWalletPageHandler(
      mojo::PendingReceiver<qorai_wallet::mojom::PageHandler> receiver,
      Profile* profile,
      ui::MojoWebUIController* webui_controller);

  AndroidWalletPageHandler(const AndroidWalletPageHandler&) = delete;
  AndroidWalletPageHandler& operator=(const AndroidWalletPageHandler&) = delete;
  ~AndroidWalletPageHandler() override;

  void ShowApprovePanelUI() override;
  void ShowWalletBackupUI() override;
  void UnlockWalletUI() override;

 private:
  raw_ptr<ui::MojoWebUIController> const webui_controller_;
};

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_WALLET_ANDROID_ANDROID_WALLET_PAGE_HANDLER_H_
