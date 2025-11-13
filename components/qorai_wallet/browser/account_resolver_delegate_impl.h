/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ACCOUNT_RESOLVER_DELEGATE_IMPL_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ACCOUNT_RESOLVER_DELEGATE_IMPL_H_

#include <string>

#include "qorai/components/qorai_wallet/browser/account_resolver_delegate.h"
#include "qorai/components/qorai_wallet/browser/keyring_service.h"

namespace qorai_wallet {

class AccountResolverDelegateImpl : public AccountResolverDelegate {
 public:
  explicit AccountResolverDelegateImpl(KeyringService& keyring_service);

  mojom::AccountIdPtr ResolveAccountId(
      const std::string* from_account_id,
      const std::string* from_address) override;
  bool ValidateAccountId(const mojom::AccountIdPtr& account_id) override;
  std::optional<std::string> ResolveAddress(
      const mojom::AccountIdPtr& account_id) override;

 private:
  raw_ref<KeyringService> keyring_service_;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ACCOUNT_RESOLVER_DELEGATE_IMPL_H_
