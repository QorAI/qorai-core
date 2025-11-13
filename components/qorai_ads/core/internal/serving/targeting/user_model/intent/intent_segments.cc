/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/targeting/user_model/intent/intent_segments.h"

#include <utility>

#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/model/purchase_intent_model.h"
#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_feature.h"

namespace qorai_ads {

void BuildIntentSegments(BuildSegmentsCallback callback) {
  SegmentList segments;

  if (base::FeatureList::IsEnabled(kPurchaseIntentFeature)) {
    segments = GetPurchaseIntentSegments();
  }

  std::move(callback).Run(segments);
}

}  // namespace qorai_ads
