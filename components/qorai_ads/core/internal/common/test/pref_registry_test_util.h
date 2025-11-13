/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_PREF_REGISTRY_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_PREF_REGISTRY_TEST_UTIL_H_

namespace qorai_ads::test {

// TODO(https://github.com/qorai/qorai-browser/issues/34528): Refactor unit test
// pref mocks to use PrefService.

void RegisterLocalStatePrefs();
void RegisterProfilePrefs();

}  // namespace qorai_ads::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_TEST_PREF_REGISTRY_TEST_UTIL_H_
