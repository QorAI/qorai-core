/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/flags/debug/debug_flag_util.h"

#include "qorai/components/qorai_ads/core/internal/global_state/global_state.h"

namespace qorai_ads {

bool ShouldDebug() {
  return GlobalState::GetInstance()->Flags().should_debug;
}

}  // namespace qorai_ads
