/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SERVICES_QORAI_WALLET_PUBLIC_CPP_QORAI_WALLET_UTILS_SERVICE_H_
#define QORAI_COMPONENTS_SERVICES_QORAI_WALLET_PUBLIC_CPP_QORAI_WALLET_UTILS_SERVICE_H_

#include "qorai/components/services/qorai_wallet/public/mojom/qorai_wallet_utils_service.mojom.h"
#include "mojo/public/cpp/bindings/pending_associated_receiver.h"
#include "mojo/public/cpp/bindings/remote.h"

namespace qorai_wallet {

/**
 * Launches and communicates mojom::QoraiWalletUtilsService in separate process.
 */
class QoraiWalletUtilsService {
 public:
  QoraiWalletUtilsService();
  ~QoraiWalletUtilsService();
  QoraiWalletUtilsService(const QoraiWalletUtilsService&) = delete;
  QoraiWalletUtilsService& operator=(const QoraiWalletUtilsService&) = delete;

  // Creates decoder in qorai wallet utils process and provides handles.
  void CreateZCashDecoder(
      mojo::PendingAssociatedReceiver<zcash::mojom::ZCashDecoder> receiver);

  static QoraiWalletUtilsService* GetInstance();

 private:
  void MaybeLaunchService();

  mojo::Remote<mojom::QoraiWalletUtilsService> qorai_wallet_utils_service_;

  base::WeakPtrFactory<QoraiWalletUtilsService> weak_ptr_factory_{this};
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_SERVICES_QORAI_WALLET_PUBLIC_CPP_QORAI_WALLET_UTILS_SERVICE_H_
