/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_COMMAND_LINE_SWITCH_TEST_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_COMMAND_LINE_SWITCH_TEST_INFO_H_

#include <string>
#include <vector>

namespace qorai_ads::test {

struct CommandLineSwitchInfo final {
  CommandLineSwitchInfo();
  CommandLineSwitchInfo(std::string key, std::string value);

  std::string key;
  std::string value;
};

using CommandLineSwitchList = std::vector<CommandLineSwitchInfo>;

}  // namespace qorai_ads::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_COMMAND_LINE_SWITCH_TEST_INFO_H_
