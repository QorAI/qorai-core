/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/targeting/user_model/latent_interest/latent_interest_segments.h"

#include <utility>

#include "qorai/components/qorai_ads/core/internal/segments/segment_alias.h"

namespace qorai_ads {

void BuildLatentInterestSegments(BuildSegmentsCallback callback) {
  std::move(callback).Run(/*segments=*/{});
}

}  // namespace qorai_ads
