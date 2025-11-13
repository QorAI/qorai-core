/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_COMMON_POST_COMMIT_TRANSACTION_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_COMMON_POST_COMMIT_TRANSACTION_H_

#include <string>

#include "qorai/components/qorai_rewards/core/engine/endpoints/request_builder.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards_engine_internal.mojom.h"

namespace qorai_rewards::internal {
class RewardsEngine;

namespace endpoints {

class PostCommitTransaction : public RequestBuilder {
 public:
  PostCommitTransaction(RewardsEngine& engine,
                        std::string&& token,
                        std::string&& address,
                        mojom::ExternalTransactionPtr);
  ~PostCommitTransaction() override;

 protected:
  std::string token_;
  std::string address_;
  mojom::ExternalTransactionPtr transaction_;
};

}  // namespace endpoints
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_COMMON_POST_COMMIT_TRANSACTION_H_
