/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ACCOUNT_RESOLVER_DELEGATE_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ACCOUNT_RESOLVER_DELEGATE_H_

#include <optional>
#include <string>

#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

namespace qorai_wallet {

// Wrapper around KeyringService for searching and validating accounts.
class AccountResolverDelegate {
 public:
  virtual ~AccountResolverDelegate() = default;

  // Searches for an existing account by persisted unique_key or address.
  virtual mojom::AccountIdPtr ResolveAccountId(
      const std::string* from_account_id,
      const std::string* from_address) = 0;

  // Returns true if there is an existing account equal to account_id.
  virtual bool ValidateAccountId(const mojom::AccountIdPtr& account_id) = 0;

  virtual std::optional<std::string> ResolveAddress(
      const mojom::AccountIdPtr& account_id) = 0;
};

}  // namespace qorai_wallet
   //
#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ACCOUNT_RESOLVER_DELEGATE_H_
