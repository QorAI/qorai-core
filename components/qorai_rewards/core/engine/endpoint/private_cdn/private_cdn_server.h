/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINT_PRIVATE_CDN_PRIVATE_CDN_SERVER_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINT_PRIVATE_CDN_PRIVATE_CDN_SERVER_H_

#include "qorai/components/qorai_rewards/core/engine/endpoint/private_cdn/get_publisher/get_publisher.h"

namespace qorai_rewards::internal {
class RewardsEngine;

namespace endpoint {

class PrivateCDNServer {
 public:
  explicit PrivateCDNServer(RewardsEngine& engine);
  ~PrivateCDNServer();

  private_cdn::GetPublisher& get_publisher() { return get_publisher_; }

 private:
  private_cdn::GetPublisher get_publisher_;
};

}  // namespace endpoint
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINT_PRIVATE_CDN_PRIVATE_CDN_SERVER_H_
