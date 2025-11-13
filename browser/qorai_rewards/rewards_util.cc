/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_rewards/rewards_util.h"

#include "base/check.h"
#include "qorai/components/qorai_rewards/core/rewards_util.h"
#include "chrome/browser/profiles/profile.h"

namespace qorai_rewards {

bool IsSupportedForProfile(Profile* profile, IsSupportedOptions options) {
  DCHECK(profile);
  return profile->IsRegularProfile() &&
         IsSupported(profile->GetPrefs(), options);
}

}  // namespace qorai_rewards
