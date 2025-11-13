/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ACCOUNT_OBSERVER_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ACCOUNT_OBSERVER_H_

#include <string>

#include "base/observer_list_types.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

struct TransactionInfo;
struct WalletInfo;

class AccountObserver : public base::CheckedObserver {
 public:
  // Invoked when the `wallet` did initialize.
  virtual void OnDidInitializeWallet(const WalletInfo& wallet) {}

  // Invoked if the wallet is invalid.
  virtual void OnFailedToInitializeWallet() {}

  // Invoked after successfully processing a deposit for `transaction`.
  virtual void OnDidProcessDeposit(const TransactionInfo& transaction) {}

  // Invoked after failing to process a deposit for `creative_instance_id`,
  // `mojom_ad_type` and `mojom_confirmation_type`.
  virtual void OnFailedToProcessDeposit(
      const std::string& creative_instance_id,
      mojom::AdType mojom_ad_type,
      mojom::ConfirmationType mojom_confirmation_type) {}
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_ACCOUNT_OBSERVER_H_
