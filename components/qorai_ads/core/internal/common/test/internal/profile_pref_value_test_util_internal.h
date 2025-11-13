/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_PROFILE_PREF_VALUE_TEST_UTIL_INTERNAL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_PROFILE_PREF_VALUE_TEST_UTIL_INTERNAL_H_

#include <string>

#include "base/values.h"

namespace qorai_ads::test {

base::Value GetProfilePrefValue(const std::string& path);

base::Value GetDefaultProfilePrefValue(const std::string& path);

void ClearProfilePrefValue(const std::string& path);

bool HasProfilePrefPathValue(const std::string& path);

}  // namespace qorai_ads::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_INTERNAL_PROFILE_PREF_VALUE_TEST_UTIL_INTERNAL_H_
