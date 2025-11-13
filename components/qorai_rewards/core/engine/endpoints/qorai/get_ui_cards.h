/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_QORAI_GET_UI_CARDS_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_QORAI_GET_UI_CARDS_H_

#include <optional>
#include <vector>

#include "base/memory/weak_ptr.h"
#include "qorai/components/qorai_rewards/core/engine/rewards_engine_helper.h"
#include "qorai/components/qorai_rewards/core/mojom/rewards.mojom.h"

namespace qorai_rewards::internal::endpoints {

// GET v1/cards
//
// Success code: HTTP_OK (200)
//
// Response body:
// {
//   "community-card": [
//     {
//       "title": "{{ title }}",
//       "description": "{{ description }}",
//       "url": "{{ link }}",
//       "thumbnail": "{{ image_url }}"
//     }
//    ]
// }
class GetUICards : public RewardsEngineHelper,
                   public WithHelperKey<GetUICards> {
 public:
  explicit GetUICards(RewardsEngine& engine);
  ~GetUICards() override;

  using Result = std::optional<std::vector<mojom::UICardPtr>>;
  using RequestCallback = base::OnceCallback<void(Result result)>;

  virtual void Request(RequestCallback callback);

 private:
  mojom::UrlRequestPtr CreateRequest();
  Result MapResponse(const mojom::UrlResponse& response);
  void OnResponse(RequestCallback callback, mojom::UrlResponsePtr response);

  base::WeakPtrFactory<GetUICards> weak_factory_{this};
};

}  // namespace qorai_rewards::internal::endpoints

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_ENDPOINTS_QORAI_GET_UI_CARDS_H_
