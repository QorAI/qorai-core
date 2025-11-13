/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/ads_client/ads_client_util.h"

#include "base/check.h"
#include "qorai/components/qorai_ads/core/internal/global_state/global_state.h"
#include "qorai/components/qorai_ads/core/public/ads_client/ads_client.h"

namespace qorai_ads {

AdsClient& GetAdsClient() {
  CHECK(GlobalState::HasInstance());

  return GlobalState::GetInstance()->GetAdsClient();
}

}  // namespace qorai_ads
