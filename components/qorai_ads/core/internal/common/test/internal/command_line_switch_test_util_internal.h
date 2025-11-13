/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_COMMAND_LINE_SWITCH_TEST_UTIL_INTERNAL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_COMMAND_LINE_SWITCH_TEST_UTIL_INTERNAL_H_

#include <optional>

namespace qorai_ads::test {

void SimulateCommandLineSwitches();
void ResetCommandLineSwitches();

std::optional<bool>& DidAppendCommandLineSwitches();

}  // namespace qorai_ads::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_COMMAND_LINE_SWITCH_TEST_UTIL_INTERNAL_H_
