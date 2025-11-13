/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_QORAI_POST_CONNECT_BITFLYER_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_QORAI_POST_CONNECT_BITFLYER_H_

#include <optional>
#include <string>

#include "qorai/components/qorai_rewards/core/engine/endpoints/common/post_connect.h"

// POST /v3/wallet/bitflyer/{rewards_payment_id}/claim
//
// clang-format off
// Request body:
// {
//   "linkingInfo": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHRlcm5hbF9hY2NvdW50X2lkMjoiMzU5Qzg1NUJCRTdBRUFENjc3QUQxMjQ5ODAzQkQ5NURBNTI3OEQ4MTU3QjU4REJCNDU0MTVEOUZBUEVBMzU4MyIsInJlcXVlc3RfaWQiOiJhM2RjHGRhYi0xZDc0LTQ0YzYtOGE5Zi34YTVhMTNhYWE0MjgiLCJ0aW1lc3RhbXAiOiIyNDIyLTA4LTE4VDIwOjM0OjA5LjE4MDIxMTFaIiwiYWNjb3VudF9oYXNoIjoiZjUwYjAxOGI1ZjJiNzVhMDBjMzBlYjI4NmEyMmJhZjExYzg4Y2VjMSIsImRlcG9zaXRfaWQiOiI4ZjgxMmU0MS0yODUyLTRmNGItOTgxNy0wNDdiZjA5NDYzZmMifQ.P9_JMU5QRwmaaDjjldXvax5WlbjxksZi7ljiKEJ5kMk"  // NOLINT
// }
// clang-format on
//
// Response body:
// {
//   "geoCountry": "JP"
// }

namespace qorai_rewards::internal {
class RewardsEngine;

namespace endpoints {

class PostConnectBitflyer final : public PostConnect {
 public:
  PostConnectBitflyer(RewardsEngine& engine, std::string&& linking_info);
  ~PostConnectBitflyer() override;

 private:
  std::optional<std::string> Content() const override;

  std::string Path(base::cstring_view payment_id) const override;

  std::string linking_info_;
};

}  // namespace endpoints
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_QORAI_POST_CONNECT_BITFLYER_H_
