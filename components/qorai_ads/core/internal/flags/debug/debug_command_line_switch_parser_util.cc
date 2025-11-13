/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/flags/debug/debug_command_line_switch_parser_util.h"

#include "qorai/components/qorai_rewards/core/rewards_flags.h"

namespace qorai_ads {

bool ParseDebugCommandLineSwitch() {
  return qorai_rewards::RewardsFlags::ForCurrentProcess().debug;
}

}  // namespace qorai_ads
