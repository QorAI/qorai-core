/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINT_PRIVATE_CDN_GET_PUBLISHER_GET_PUBLISHER_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINT_PRIVATE_CDN_GET_PUBLISHER_GET_PUBLISHER_H_

#include <string>

#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards.mojom.h"

// GET /publishers/prefixes/{prefix}
//
// Success code:
// HTTP_OK (200)
//
// Error codes:
// HTTP_NOT_FOUND (404)
//
// Response body:
// See
// https://github.com/qorai/qorai-core/blob/master/components/qorai_rewards/core/engine/publisher/protos/channel_response.proto

namespace qorai_rewards::internal {
class RewardsEngine;

namespace endpoint {
namespace private_cdn {

using GetPublisherCallback =
    base::OnceCallback<void(const mojom::Result result,
                            mojom::ServerPublisherInfoPtr info)>;

class GetPublisher {
 public:
  explicit GetPublisher(RewardsEngine& engine);
  ~GetPublisher();

  void Request(const std::string& publisher_key,
               const std::string& hash_prefix,
               GetPublisherCallback callback);

 private:
  std::string GetUrl(const std::string& hash_prefix);

  mojom::Result CheckStatusCode(const int status_code);

  mojom::Result ParseBody(const std::string& body,
                          const std::string& publisher_key,
                          mojom::ServerPublisherInfo* info);

  void OnRequest(const std::string& publisher_key,
                 GetPublisherCallback callback,
                 mojom::UrlResponsePtr response);

  const raw_ref<RewardsEngine> engine_;
};

}  // namespace private_cdn
}  // namespace endpoint
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINT_PRIVATE_CDN_GET_PUBLISHER_GET_PUBLISHER_H_
