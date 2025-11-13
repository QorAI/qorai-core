/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_ZEBPAY_GET_BALANCE_ZEBPAY_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_ZEBPAY_GET_BALANCE_ZEBPAY_H_

#include <optional>
#include <string>
#include <vector>

#include "qorai/components/qorai_rewards/core/engine/endpoints/request_builder.h"
#include "qorai/components/qorai_rewards/core/engine/endpoints/response_handler.h"
#include "qorai/components/qorai_rewards/core/engine/endpoints/result_for.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards_engine_internal.mojom.h"

// GET /api/balance
//
// Request body:
// -
//
// Response body:
// {
//   "QOR": 0
// }

namespace qorai_rewards::internal {
class RewardsEngine;

namespace endpoints {

class GetBalanceZebPay;

template <>
struct ResultFor<GetBalanceZebPay> {
  using Value = double;  // balance
  using Error = mojom::GetBalanceZebPayError;
};

class GetBalanceZebPay final : public RequestBuilder,
                               public ResponseHandler<GetBalanceZebPay> {
 public:
  static Result ProcessResponse(RewardsEngine& engine,
                                const mojom::UrlResponse& response);

  GetBalanceZebPay(RewardsEngine& engine, std::string&& token);
  ~GetBalanceZebPay() override;

 private:
  std::optional<std::string> Url() const override;
  mojom::UrlMethod Method() const override;
  std::optional<std::vector<std::string>> Headers(
      const std::string& content) const override;

  std::string token_;
};

}  // namespace endpoints
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_ZEBPAY_GET_BALANCE_ZEBPAY_H_
