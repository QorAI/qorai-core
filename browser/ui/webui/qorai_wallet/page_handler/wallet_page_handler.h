// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_WALLET_PAGE_HANDLER_WALLET_PAGE_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_WALLET_PAGE_HANDLER_WALLET_PAGE_HANDLER_H_

#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/remote.h"

class Profile;

class WalletPageHandler : public qorai_wallet::mojom::PageHandler {
 public:
  WalletPageHandler(
      mojo::PendingReceiver<qorai_wallet::mojom::PageHandler> receiver,
      Profile* profile);

  WalletPageHandler(const WalletPageHandler&) = delete;
  WalletPageHandler& operator=(const WalletPageHandler&) = delete;
  ~WalletPageHandler() override;

  void ShowApprovePanelUI() override;
  void ShowWalletBackupUI() override;
  void UnlockWalletUI() override;

 private:
  raw_ptr<Profile> profile_ = nullptr;  // NOT OWNED
  mojo::Receiver<qorai_wallet::mojom::PageHandler> receiver_;
  base::WeakPtrFactory<WalletPageHandler> weak_ptr_factory_;
};

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_WALLET_PAGE_HANDLER_WALLET_PAGE_HANDLER_H_
