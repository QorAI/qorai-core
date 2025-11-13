/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_PROVIDER_BITFLYER_BITFLYER_TRANSFER_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_PROVIDER_BITFLYER_BITFLYER_TRANSFER_H_

#include "qorai/components/qorai_rewards/core/engine/endpoints/bitflyer/post_commit_transaction_bitflyer.h"
#include "qorai/components/qorai_rewards/core/engine/wallet_provider/transfer.h"

namespace qorai_rewards::internal::bitflyer {

class BitFlyerTransfer final : public wallet_provider::Transfer {
 public:
  using Transfer::Transfer;

 private:
  void CommitTransaction(ResultCallback,
                         mojom::ExternalTransactionPtr) const override;

  void OnCommitTransaction(
      ResultCallback,
      endpoints::PostCommitTransactionBitFlyer::Result&&) const;
};

}  // namespace qorai_rewards::internal::bitflyer

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_PROVIDER_BITFLYER_BITFLYER_TRANSFER_H_
