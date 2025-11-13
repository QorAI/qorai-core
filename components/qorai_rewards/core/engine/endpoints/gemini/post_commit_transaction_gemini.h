/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_GEMINI_POST_COMMIT_TRANSACTION_GEMINI_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_GEMINI_POST_COMMIT_TRANSACTION_GEMINI_H_

#include <optional>
#include <string>
#include <vector>

#include "qorai/components/qorai_rewards/core/engine/endpoints/common/post_commit_transaction.h"
#include "qorai/components/qorai_rewards/core/engine/endpoints/response_handler.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards_engine_internal.mojom.h"

// POST /v1/payments/pay
//
// Request body:
// -
//
// Response body:
// {
//   "amount": 0.95,
//   "currency": "QOR",
//   "destination": "621e9ca3-6c64-4055-bce7-e3460841a7cc",
//   "result": "OK",
//   "status": "Pending",
//   "tx_ref": "c40ccc6a-8579-6435-90be-66ea7ea96c1b"
// }

namespace qorai_rewards::internal::endpoints {

class PostCommitTransactionGemini;

template <>
struct ResultFor<PostCommitTransactionGemini> {
  using Value = void;
  using Error = mojom::PostCommitTransactionGeminiError;
};

class PostCommitTransactionGemini final
    : public PostCommitTransaction,
      public ResponseHandler<PostCommitTransactionGemini> {
 public:
  using PostCommitTransaction::PostCommitTransaction;

  static Result ProcessResponse(RewardsEngine& engine,
                                const mojom::UrlResponse&);

 private:
  std::optional<std::string> Url() const override;
  std::optional<std::vector<std::string>> Headers(
      const std::string& content) const override;
  std::string ContentType() const override;
};

}  // namespace qorai_rewards::internal::endpoints

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_GEMINI_POST_COMMIT_TRANSACTION_GEMINI_H_
