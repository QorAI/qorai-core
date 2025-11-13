/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_COMMAND_LINE_SWITCH_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_COMMAND_LINE_SWITCH_TEST_UTIL_H_

#include <string>

#include "qorai/components/qorai_ads/core/internal/common/test/command_line_switch_test_info.h"

namespace qorai_ads::test {

// Should only be called from `test::TestBase::SetUpMocks`.
void AppendCommandLineSwitches(
    const CommandLineSwitchList& command_line_switches);

std::string ToString(const CommandLineSwitchInfo& command_line_switch);

}  // namespace qorai_ads::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_COMMAND_LINE_SWITCH_TEST_UTIL_H_
