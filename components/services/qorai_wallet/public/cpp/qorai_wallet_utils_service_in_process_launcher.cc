/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SERVICES_QORAI_WALLET_CONTENT_QORAI_WALLET_UTILS_SERVICE_LAUNCHER_H_
#define QORAI_COMPONENTS_SERVICES_QORAI_WALLET_CONTENT_QORAI_WALLET_UTILS_SERVICE_LAUNCHER_H_

#include "qorai/components/services/qorai_wallet/public/cpp/qorai_wallet_utils_service_in_process_launcher.h"

#include <memory>
#include <utility>

#include "qorai/components/services/qorai_wallet/qorai_wallet_utils_service_impl.h"
#include "mojo/public/cpp/bindings/self_owned_receiver.h"

namespace qorai_wallet {

void LaunchInProcessQoraiWalletUtilsService(
    mojo::PendingReceiver<mojom::QoraiWalletUtilsService> receiver) {
  mojo::MakeSelfOwnedReceiver(
      std::make_unique<QoraiWalletUtilsServiceImpl>(
          mojo::PendingReceiver<mojom::QoraiWalletUtilsService>()),
      std::move(receiver));
}

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_SERVICES_QORAI_WALLET_CONTENT_QORAI_WALLET_UTILS_SERVICE_LAUNCHER_H_
