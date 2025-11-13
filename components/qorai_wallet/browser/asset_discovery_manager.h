/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ASSET_DISCOVERY_MANAGER_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ASSET_DISCOVERY_MANAGER_H_

#include <map>
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "base/gtest_prod_util.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "qorai/components/api_request_helper/api_request_helper.h"
#include "qorai/components/qorai_wallet/browser/asset_discovery_task.h"
#include "qorai/components/qorai_wallet/browser/keyring_service_observer_base.h"
#include "qorai/components/qorai_wallet/browser/simple_hash_client.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "mojo/public/cpp/bindings/receiver.h"

class PrefService;

namespace qorai_wallet {

class QoraiWalletService;
class JsonRpcService;
class SimpleHashClient;
class KeyringService;

class AssetDiscoveryManager : public KeyringServiceObserverBase {
 public:
  using APIRequestHelper = api_request_helper::APIRequestHelper;
  using APIRequestResult = api_request_helper::APIRequestResult;
  AssetDiscoveryManager(
      scoped_refptr<network::SharedURLLoaderFactory> url_loader_factory,
      QoraiWalletService& wallet_service,
      JsonRpcService& json_rpc_service,
      KeyringService& keyring_service,
      SimpleHashClient& simple_hash_client,
      PrefService* prefs);

  AssetDiscoveryManager(const AssetDiscoveryManager&) = delete;
  AssetDiscoveryManager& operator=(AssetDiscoveryManager&) = delete;
  ~AssetDiscoveryManager() override;

  // KeyringServiceObserverBase:
  void AccountsAdded(
      std::vector<mojom::AccountInfoPtr> added_accounts) override;

  // Called by frontend via QoraiWalletService and when new accounts are added
  // via the KeyringServiceObserver implementation
  void DiscoverAssetsOnAllSupportedChains(
      std::vector<mojom::AccountIdPtr> accounts,
      bool bypass_rate_limit);

  void SetQueueForTesting(
      std::queue<std::unique_ptr<AssetDiscoveryTask>> queue) {
    queue_ = std::move(queue);
  }

  size_t GetQueueSizeForTesting() { return queue_.size(); }

 private:
  friend class AssetDiscoveryManagerUnitTest;
  FRIEND_TEST_ALL_PREFIXES(AssetDiscoveryManagerUnitTest,
                           GetFungibleSupportedChains);
  FRIEND_TEST_ALL_PREFIXES(AssetDiscoveryManagerUnitTest,
                           GetNonFungibleSupportedChains);

  std::vector<mojom::ChainIdPtr> GetFungibleSupportedChains();
  std::vector<mojom::ChainIdPtr> GetNonFungibleSupportedChains();

  void AddTask(std::vector<mojom::AccountIdPtr> accounts);
  void FinishTask();

  std::unique_ptr<APIRequestHelper> api_request_helper_;
  std::queue<std::unique_ptr<AssetDiscoveryTask>> queue_;
  raw_ref<QoraiWalletService> wallet_service_;
  raw_ref<JsonRpcService> json_rpc_service_;
  raw_ref<KeyringService> keyring_service_;
  raw_ref<SimpleHashClient> simple_hash_client_;
  raw_ptr<PrefService> prefs_;
  mojo::Receiver<qorai_wallet::mojom::KeyringServiceObserver>
      keyring_service_observer_receiver_{this};
  base::WeakPtrFactory<AssetDiscoveryManager> weak_ptr_factory_;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ASSET_DISCOVERY_MANAGER_H_
