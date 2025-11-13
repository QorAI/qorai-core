/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/confirmations/queue/queue_item/confirmation_queue_item_builder_util.h"

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/internal/account/confirmations/confirmations_feature.h"
#include "qorai/components/qorai_ads/core/internal/common/random/random_util.h"
#include "qorai/components/qorai_ads/core/internal/flags/debug/debug_flag_util.h"

namespace qorai_ads {

namespace {
constexpr base::TimeDelta kDebugRetryProcessingAfter = base::Seconds(5);
}  // namespace

base::TimeDelta RetryProcessingConfirmationAfter() {
  return ShouldDebug() ? kDebugRetryProcessingAfter
                       : RandTimeDelta(kRetryProcessingConfirmationAfter.Get());
}

}  // namespace qorai_ads
