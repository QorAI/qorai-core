/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINT_GEMINI_POST_OAUTH_POST_OAUTH_GEMINI_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINT_GEMINI_POST_OAUTH_POST_OAUTH_GEMINI_H_

#include <string>

#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_rewards/core/engine/rewards_callbacks.h"

// POST https://exchange.sandbox.gemini.com/auth/token
//
// Request body:
// {
//   "client_id": "xxxxx",
//   "client_secret": "yyyyy",
//   "code": "aaaaa",
//   "grant_type": "authorization_code",
//   "redirect_uri": "rewards://gemini/authorization"
// }
//
// Success code:
// HTTP_OK (200)
//
// Error codes:
// HTTP_UNAUTHORIZED (401)
//
// Response body:
// {
//   "access_token": "aaaaa",
//   "expires_in": 83370,
//   "scope":
//   "account:read,addresses:create,balances:read,orders:create,orders:read,payments:create,payments:read,payments:send",
//   "refresh_token":"bbbbb",
//   "token_type": "Bearer"
// }

namespace qorai_rewards::internal {
class RewardsEngine;

namespace endpoint::gemini {

using PostOauthCallback =
    base::OnceCallback<void(mojom::Result, std::string&& token)>;

class PostOauth {
 public:
  explicit PostOauth(RewardsEngine& engine);
  ~PostOauth();

  void Request(const std::string& external_account_id,
               const std::string& code,
               PostOauthCallback);

 private:
  std::string GetUrl();

  std::string GeneratePayload(const std::string& external_account_id,
                              const std::string& code);

  mojom::Result ParseBody(const std::string& body, std::string* token);

  void OnRequest(PostOauthCallback, mojom::UrlResponsePtr);

  const raw_ref<RewardsEngine> engine_;
};

}  // namespace endpoint::gemini
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINT_GEMINI_POST_OAUTH_POST_OAUTH_GEMINI_H_
