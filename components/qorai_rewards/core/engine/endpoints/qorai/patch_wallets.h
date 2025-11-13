/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_QORAI_PATCH_WALLETS_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_QORAI_PATCH_WALLETS_H_

#include <optional>
#include <string>
#include <vector>

#include "qorai/components/qorai_rewards/core/engine/endpoints/request_builder.h"
#include "qorai/components/qorai_rewards/core/engine/endpoints/response_handler.h"
#include "qorai/components/qorai_rewards/core/engine/endpoints/result_for.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards.mojom.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards_engine_internal.mojom.h"

// PATCH /v4/wallets/<rewards_payment_id>
//
// Request body:
// {
//   "geo_country": "US"
// }
//
// Response body: -

namespace qorai_rewards::internal {
class RewardsEngine;

namespace endpoints {

class PatchWallets;

template <>
struct ResultFor<PatchWallets> {
  using Value = void;
  using Error = mojom::PatchWalletsError;
};

class PatchWallets final : public RequestBuilder,
                           public ResponseHandler<PatchWallets> {
 public:
  static Result ProcessResponse(RewardsEngine& engine,
                                const mojom::UrlResponse&);

  PatchWallets(RewardsEngine& engine, std::string&& geo_country);
  ~PatchWallets() override;

 private:
  std::optional<std::string> Url() const override;
  mojom::UrlMethod Method() const override;
  std::optional<std::vector<std::string>> Headers(
      const std::string& content) const override;
  std::optional<std::string> Content() const override;
  std::string ContentType() const override;

  std::string geo_country_;
};

}  // namespace endpoints
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_QORAI_PATCH_WALLETS_H_
