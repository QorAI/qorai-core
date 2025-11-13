/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_data/fixed/version_number_user_data.h"

#include "qorai/components/qorai_ads/core/internal/application_state/browser_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings.h"

namespace qorai_ads {

namespace {
constexpr char kVersionNumberKey[] = "versionNumber";
}  // namespace

base::Value::Dict BuildVersionNumberUserData() {
  if (!UserHasJoinedQoraiRewards()) {
    return {};
  }

  return base::Value::Dict().Set(kVersionNumberKey, GetBrowserVersionNumber());
}

}  // namespace qorai_ads
