/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_WALLET_HANDLER_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_WALLET_HANDLER_H_

#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/receiver.h"

namespace qorai_wallet {

class QoraiWalletService;

class WalletHandler : public mojom::WalletHandler {
 public:
  WalletHandler(mojo::PendingReceiver<mojom::WalletHandler> receiver,
                QoraiWalletService* wallet_service);

  WalletHandler(const WalletHandler&) = delete;
  WalletHandler& operator=(const WalletHandler&) = delete;
  ~WalletHandler() override;

  // mojom::WalletHandler:
  void GetWalletInfo(GetWalletInfoCallback) override;

 private:
  mojo::Receiver<mojom::WalletHandler> receiver_;

  const raw_ptr<QoraiWalletService> qorai_wallet_service_ = nullptr;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_WALLET_HANDLER_H_
