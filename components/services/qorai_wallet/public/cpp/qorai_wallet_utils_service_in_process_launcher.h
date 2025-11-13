/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SERVICES_QORAI_WALLET_PUBLIC_CPP_QORAI_WALLET_UTILS_SERVICE_IN_PROCESS_LAUNCHER_H_
#define QORAI_COMPONENTS_SERVICES_QORAI_WALLET_PUBLIC_CPP_QORAI_WALLET_UTILS_SERVICE_IN_PROCESS_LAUNCHER_H_

#include "qorai/components/services/qorai_wallet/public/mojom/qorai_wallet_utils_service.mojom.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"

namespace qorai_wallet {

void LaunchInProcessQoraiWalletUtilsService(
    mojo::PendingReceiver<mojom::QoraiWalletUtilsService> receiver);

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_SERVICES_QORAI_WALLET_PUBLIC_CPP_QORAI_WALLET_UTILS_SERVICE_IN_PROCESS_LAUNCHER_H_
