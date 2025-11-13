/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINT_GEMINI_POST_RECIPIENT_ID_POST_RECIPIENT_ID_GEMINI_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINT_GEMINI_POST_RECIPIENT_ID_POST_RECIPIENT_ID_GEMINI_H_

#include <string>

#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards.mojom.h"

// POST https://api.gemini.com/v1/payments/recipientIds
// Payload:
// {
//    "label": <uuid>
// }
//
// Headers:
//   Authorization: Bearer <token>
//   X-GEMINI-PAYLOAD: base64-payload
//
// Request body:
// {}
//
// Success code:
// HTTP_OK (200)
//
// Error codes:
// HTTP_UNAUTHORIZED (401)
// HTTP_NOT_FOUND (404)
//
// Response body:
// {
//    "result": "OK",
//    "recipient_id": "60f9be89-ada7-486d-9cef-f6d3a10886d7",
//    "label": <uuid>
// }

namespace qorai_rewards::internal {
class RewardsEngine;

namespace endpoint::gemini {

using PostRecipientIdCallback =
    base::OnceCallback<void(mojom::Result, std::string&& recipient_id)>;

class PostRecipientId {
 public:
  // TODO(https://github.com/qorai/qorai-browser/issues/48713): This is a case
  // of
  // `-Wexit-time-destructors` violation and `[[clang::no_destroy]]` has been
  // added in the meantime to fix the build error. Remove this attribute and
  // provide a proper fix.
  [[clang::no_destroy]] static inline const std::string kRecipientLabel =
      "Qorai Browser";

  explicit PostRecipientId(RewardsEngine& engine);
  ~PostRecipientId();

  void Request(const std::string& token, PostRecipientIdCallback);

 private:
  std::string GetUrl();

  mojom::Result ParseBody(const std::string& body, std::string* recipient_id);

  void OnRequest(PostRecipientIdCallback, mojom::UrlResponsePtr);
  std::string GeneratePayload();

  const raw_ref<RewardsEngine> engine_;
};

}  // namespace endpoint::gemini
}  // namespace qorai_rewards::internal

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINT_GEMINI_POST_RECIPIENT_ID_POST_RECIPIENT_ID_GEMINI_H_
