/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SERVICES_QORAI_WALLET_QORAI_WALLET_UTILS_SERVICE_IMPL_H_
#define QORAI_COMPONENTS_SERVICES_QORAI_WALLET_QORAI_WALLET_UTILS_SERVICE_IMPL_H_

#include "qorai/components/services/qorai_wallet/public/mojom/qorai_wallet_utils_service.mojom.h"
#include "qorai/components/services/qorai_wallet/public/mojom/zcash_decoder.mojom.h"
#include "mojo/public/cpp/bindings/pending_associated_remote.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/self_owned_associated_receiver.h"

namespace qorai_wallet {

class QoraiWalletUtilsServiceImpl : public mojom::QoraiWalletUtilsService {
 public:
  explicit QoraiWalletUtilsServiceImpl(
      mojo::PendingReceiver<mojom::QoraiWalletUtilsService> receiver);

  ~QoraiWalletUtilsServiceImpl() override;

  QoraiWalletUtilsServiceImpl(const QoraiWalletUtilsServiceImpl&) = delete;
  QoraiWalletUtilsServiceImpl& operator=(const QoraiWalletUtilsServiceImpl&) =
      delete;

  void CreateZCashDecoderService(
      mojo::PendingAssociatedReceiver<zcash::mojom::ZCashDecoder>
          zcash_decoder_receiver) override;

 private:
  mojo::Receiver<mojom::QoraiWalletUtilsService> receiver_;
  mojo::SelfOwnedAssociatedReceiverRef<zcash::mojom::ZCashDecoder> instance_;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_SERVICES_QORAI_WALLET_QORAI_WALLET_UTILS_SERVICE_IMPL_H_
