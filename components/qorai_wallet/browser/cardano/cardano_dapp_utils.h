/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_CARDANO_CARDANO_DAPP_UTILS_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_CARDANO_CARDANO_DAPP_UTILS_H_

#include <string>
#include <vector>

#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

namespace qorai_wallet {

class QoraiWalletProviderDelegate;
class KeyringService;

std::vector<std::string> GetCardanoAccountPermissionIdentifiers(
    KeyringService* keyring_service);

mojom::AccountIdPtr GetCardanoPreferredDappAccount(
    QoraiWalletProviderDelegate* delegate,
    KeyringService* keyring_service);

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_CARDANO_CARDANO_DAPP_UTILS_H_
