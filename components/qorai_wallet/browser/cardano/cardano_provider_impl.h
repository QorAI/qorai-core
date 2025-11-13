/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_CARDANO_CARDANO_PROVIDER_IMPL_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_CARDANO_CARDANO_PROVIDER_IMPL_H_

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "base/memory/raw_ref.h"
#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_provider_delegate.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/keyring_service_observer_base.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "mojo/public/cpp/bindings/unique_receiver_set.h"

namespace qorai_wallet {

class CardanoProviderImpl final : public mojom::CardanoProvider,
                                  public KeyringServiceObserverBase {
 public:
  using QoraiWalletProviderDelegateFactory =
      base::RepeatingCallback<std::unique_ptr<QoraiWalletProviderDelegate>()>;

  CardanoProviderImpl(const CardanoProviderImpl&) = delete;
  CardanoProviderImpl& operator=(const CardanoProviderImpl&) = delete;
  CardanoProviderImpl(QoraiWalletService& qorai_wallet_service,
                      QoraiWalletProviderDelegateFactory delegate_factory);
  ~CardanoProviderImpl() override;

  // mojom::CardanoProvider
  void Enable(mojo::PendingReceiver<mojom::CardanoApi> cardano_api,
              EnableCallback callback) override;
  void IsEnabled(IsEnabledCallback callback) override;


 private:
  enum class PermissionCheckResult {
    kTabInactive,
    kDeniedGlobally,
    kWalletNotCreated,
    kNoAccounts,
    kWalletLocked,
    kGetAllowedAccountsFailed,
    kHasAllowedAccounts,
    kNeedsPermissionRequest
  };

  friend class CardanoProviderImplUnitTest;

  PermissionCheckResult EvaluatePermissionsState(
      std::vector<std::string>& allowed_accounts);

  mojom::AccountIdPtr GetAllowedSelectedAccount();

  QoraiWalletProviderDelegate* delegate();

  // KeyringServiceObserverBase:
  void Locked() override;
  void Unlocked() override;
  void SelectedDappAccountChanged(mojom::CoinType coin,
                                  mojom::AccountInfoPtr account) override;

  void RequestCardanoPermissions(
      mojo::PendingReceiver<mojom::CardanoApi> cardano_api,
      EnableCallback callback,
      const url::Origin& origin);

  void OnRequestCardanoPermissions(
      mojo::PendingReceiver<mojom::CardanoApi> cardano_api,
      EnableCallback callback,
      const url::Origin& origin,
      mojom::RequestPermissionsError error,
      const std::optional<std::vector<std::string>>& allowed_accounts);

  raw_ref<QoraiWalletService> qorai_wallet_service_;
  QoraiWalletProviderDelegateFactory delegate_factory_;
  std::unique_ptr<QoraiWalletProviderDelegate> delegate_;

  EnableCallback pending_request_cardano_permissions_callback_;
  mojo::PendingReceiver<mojom::CardanoApi> pending_cardano_api_;
  url::Origin pending_request_cardano_permissions_origin_;
  bool wallet_page_shown_ = false;

  mojo::Receiver<mojom::KeyringServiceObserver> keyring_observer_receiver_{
      this};

  mojo::UniqueReceiverSet<mojom::CardanoApi> cardano_api_receivers_;

  base::WeakPtrFactory<CardanoProviderImpl> weak_ptr_factory_{this};
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_CARDANO_CARDANO_PROVIDER_IMPL_H_
