/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_PROVIDER_GEMINI_GEMINI_TRANSFER_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_PROVIDER_GEMINI_GEMINI_TRANSFER_H_

#include "qorai/components/qorai_rewards/core/engine/endpoints/gemini/post_commit_transaction_gemini.h"
#include "qorai/components/qorai_rewards/core/engine/wallet_provider/transfer.h"

namespace qorai_rewards::internal::gemini {

class GeminiTransfer final : public wallet_provider::Transfer {
 public:
  using Transfer::Transfer;

 private:
  void CommitTransaction(ResultCallback,
                         mojom::ExternalTransactionPtr) const override;

  void OnCommitTransaction(
      ResultCallback,
      endpoints::PostCommitTransactionGemini::Result&&) const;
};

}  // namespace qorai_rewards::internal::gemini

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_WALLET_PROVIDER_GEMINI_GEMINI_TRANSFER_H_
