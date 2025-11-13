/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_POLKADOT_POLKADOT_WALLET_SERVICE_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_POLKADOT_POLKADOT_WALLET_SERVICE_H_

#include "qorai/components/qorai_wallet/browser/keyring_service_observer_base.h"
#include "qorai/components/qorai_wallet/browser/polkadot/polkadot_substrate_rpc.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "mojo/public/cpp/bindings/receiver_set.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"

namespace qorai_wallet {

class KeyringService;
class NetworkManager;

// The main Polkadot-based interface that the front-end interacts with.
class PolkadotWalletService : public mojom::PolkadotWalletService,
                              public KeyringServiceObserverBase {
 public:
  PolkadotWalletService(
      KeyringService& keyring_service,
      NetworkManager& network_manager,
      scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory);

  ~PolkadotWalletService() override;

  // Adds a PolkadotWalletService to the internal ReceiverSet.
  void Bind(mojo::PendingReceiver<mojom::PolkadotWalletService> receiver);

  // Invalidates all the weak ptrs in use by this service.
  void Reset();

  // Get the name of the chain currently pointed to by the current network
  // configuration.
  void GetNetworkName(mojom::AccountIdPtr account_id,
                      GetNetworkNameCallback callback) override;

  void GetAccountBalance(mojom::AccountIdPtr account,
                         const std::string& chain_id,
                         GetAccountBalanceCallback callback) override;

 private:
  const raw_ref<KeyringService> keyring_service_;
  mojo::ReceiverSet<mojom::PolkadotWalletService> receivers_;

  PolkadotSubstrateRpc polkadot_substrate_rpc_;
  mojo::Receiver<qorai_wallet::mojom::KeyringServiceObserver>
      keyring_service_observer_receiver_{this};
  base::WeakPtrFactory<PolkadotWalletService> weak_ptr_factory_{this};
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_POLKADOT_POLKADOT_WALLET_SERVICE_H_
