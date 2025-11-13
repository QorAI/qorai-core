/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_BITFLYER_POST_COMMIT_TRANSACTION_BITFLYER_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_BITFLYER_POST_COMMIT_TRANSACTION_BITFLYER_H_

#include <optional>
#include <string>
#include <vector>

#include "qorai/components/qorai_rewards/core/engine/endpoints/common/post_commit_transaction.h"
#include "qorai/components/qorai_rewards/core/engine/endpoints/response_handler.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards_engine_internal.mojom.h"

// POST /api/link/v1/coin/withdraw-to-deposit-id/request
//
// Request body:
// {
//   "amount": "0.950000",
//   "currency_code": "QOR",
//   "deposit_id": "b3149e8b-0001-4588-a243-ed792d445469",
//   "dry_run": false,
//   "transfer_id": "72a46abc-0683-4716-a1ba-52dc130b3dba"
// }
//
// Response body:
// {
//   "amount": 0.95,
//   "currency_code": "QOR",
//   "dry_run": false,
//   "message": null,
//   "transfer_id": "72a46abc-0683-4716-a1ba-52dc130b3dba",
//   "transfer_status": "SUCCESS"
// }

namespace qorai_rewards::internal::endpoints {

class PostCommitTransactionBitFlyer;

template <>
struct ResultFor<PostCommitTransactionBitFlyer> {
  using Value = void;
  using Error = mojom::PostCommitTransactionBitFlyerError;
};

class PostCommitTransactionBitFlyer final
    : public PostCommitTransaction,
      public ResponseHandler<PostCommitTransactionBitFlyer> {
 public:
  using PostCommitTransaction::PostCommitTransaction;

  static Result ProcessResponse(RewardsEngine& engine,
                                const mojom::UrlResponse&);

 private:
  std::optional<std::string> Url() const override;
  std::optional<std::vector<std::string>> Headers(
      const std::string& content) const override;
  std::optional<std::string> Content() const override;
  std::string ContentType() const override;
};

}  // namespace qorai_rewards::internal::endpoints

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_BITFLYER_POST_COMMIT_TRANSACTION_BITFLYER_H_
