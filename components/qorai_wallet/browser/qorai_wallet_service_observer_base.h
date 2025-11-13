/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_QORAI_WALLET_SERVICE_OBSERVER_BASE_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_QORAI_WALLET_SERVICE_OBSERVER_BASE_H_

#include <string>
#include <vector>

#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

namespace qorai_wallet {

class QoraiWalletServiceObserverBase
    : public mojom::QoraiWalletServiceObserver {
  void OnActiveOriginChanged(mojom::OriginInfoPtr origin_info) override {}
  void OnDefaultEthereumWalletChanged(mojom::DefaultWallet wallet) override {}
  void OnDefaultSolanaWalletChanged(mojom::DefaultWallet wallet) override {}
  void OnDefaultCardanoWalletChanged(mojom::DefaultWallet wallet) override {}
  void OnDefaultBaseCurrencyChanged(const std::string& currency) override {}
  void OnDefaultBaseCryptocurrencyChanged(
      const std::string& cryptocurrency) override {}
  void OnNetworkListChanged() override {}
  void OnDiscoverAssetsStarted() override {}
  void OnDiscoverAssetsCompleted(
      std::vector<mojom::BlockchainTokenPtr> discovered_assets) override {}
  void OnResetWallet() override {}
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_QORAI_WALLET_SERVICE_OBSERVER_BASE_H_
