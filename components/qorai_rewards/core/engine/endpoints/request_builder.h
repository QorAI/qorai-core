/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_REQUEST_BUILDER_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_REQUEST_BUILDER_H_

#include <optional>
#include <string>
#include <vector>

#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards.mojom.h"

namespace qorai_rewards::internal {
class RewardsEngine;

namespace endpoints {

class RequestBuilder {
 public:
  static constexpr char kApplicationJson[] = "application/json; charset=utf-8";

  virtual ~RequestBuilder();

  std::optional<mojom::UrlRequestPtr> Request() const;

 protected:
  explicit RequestBuilder(RewardsEngine& engine);

  virtual std::optional<std::string> Url() const = 0;

  virtual mojom::UrlMethod Method() const;

  virtual std::optional<std::vector<std::string>> Headers(
      const std::string& content) const;

  virtual std::optional<std::string> Content() const;

  virtual std::string ContentType() const;

  virtual bool SkipLog() const;

  virtual uint32_t LoadFlags() const;

  const raw_ref<RewardsEngine> engine_;
};

}  // namespace endpoints
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_REQUEST_BUILDER_H_
