/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_wallet/browser/wallet_handler.h"

#include <utility>

#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/keyring_service.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/components/qorai_wallet/common/common_utils.h"

namespace qorai_wallet {

WalletHandler::WalletHandler(
    mojo::PendingReceiver<mojom::WalletHandler> receiver,
    QoraiWalletService* wallet_service)
    : receiver_(this, std::move(receiver)),
      qorai_wallet_service_(wallet_service) {}

WalletHandler::~WalletHandler() = default;

// TODO(apaymyshev): this is the only method in WalletHandler. Should be merged
// into QoraiWalletService.
void WalletHandler::GetWalletInfo(GetWalletInfoCallback callback) {
  if (!qorai_wallet_service_) {
    std::move(callback).Run(nullptr);
    return;
  }

  auto* keyring_service = qorai_wallet_service_->keyring_service();

  std::move(callback).Run(mojom::WalletInfo::New(
      keyring_service->IsWalletCreatedSync(), keyring_service->IsLockedSync(),
      keyring_service->IsWalletBackedUpSync(), IsBitcoinEnabled(),
      IsBitcoinImportEnabled(), IsBitcoinLedgerEnabled(), IsZCashEnabled(),
      IsAnkrBalancesEnabled(), IsTransactionSimulationsEnabled(),
      IsZCashShieldedTransactionsEnabled(), IsCardanoEnabled(),
      GetEnabledCoins(), IsCardanoDAppSupportEnabled(), IsPolkadotEnabled()));
}

}  // namespace qorai_wallet
