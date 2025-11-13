/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_FLAGS_ADS_UUIDS_ADS_UUIDS_COMMAND_LINE_SWITCH_PARSER_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_FLAGS_ADS_UUIDS_ADS_UUIDS_COMMAND_LINE_SWITCH_PARSER_UTIL_H_

#include <string>

#include "base/containers/flat_map.h"

namespace qorai_ads {

base::flat_map<std::string, bool> ParseAdsUuidsCommandLineSwitch();

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_FLAGS_ADS_UUIDS_ADS_UUIDS_COMMAND_LINE_SWITCH_PARSER_UTIL_H_
