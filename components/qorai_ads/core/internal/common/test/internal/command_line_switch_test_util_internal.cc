/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/test/internal/command_line_switch_test_util_internal.h"

#include "qorai/components/qorai_rewards/core/rewards_flags.h"

namespace qorai_ads::test {

void SimulateCommandLineSwitches() {
  qorai_rewards::RewardsFlags::SetForceParsingForTesting(true);
}

void ResetCommandLineSwitches() {
  qorai_rewards::RewardsFlags::SetForceParsingForTesting(false);
}

std::optional<bool>& DidAppendCommandLineSwitches() {
  static std::optional<bool> did_append;
  return did_append;
}

}  // namespace qorai_ads::test
