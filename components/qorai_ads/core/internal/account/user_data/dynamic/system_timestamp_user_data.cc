/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_data/dynamic/system_timestamp_user_data.h"

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/internal/common/time/time_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings.h"

namespace qorai_ads {

namespace {
constexpr char kSystemTimestampKey[] = "systemTimestamp";
}  // namespace

base::Value::Dict BuildSystemTimestampUserData() {
  if (!UserHasJoinedQoraiRewards()) {
    return {};
  }

  return base::Value::Dict().Set(
      kSystemTimestampKey, TimeToPrivacyPreservingIso8601(base::Time::Now()));
}

}  // namespace qorai_ads
