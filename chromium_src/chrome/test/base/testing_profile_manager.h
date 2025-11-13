/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_TEST_BASE_TESTING_PROFILE_MANAGER_H_
#define QORAI_CHROMIUM_SRC_CHROME_TEST_BASE_TESTING_PROFILE_MANAGER_H_

// Reinstating `SetProfileAsLastUsed` as it has been deleted upstream, however
// this function is still in use in by `QoraiWhatsNewTest`.
#define DeleteProfileAttributesStorage        \
  SetProfileAsLastUsed(Profile* last_active); \
  void DeleteProfileAttributesStorage

#include <chrome/test/base/testing_profile_manager.h>  // IWYU pragma: export

#undef DeleteProfileAttributesStorage

#endif  // QORAI_CHROMIUM_SRC_CHROME_TEST_BASE_TESTING_PROFILE_MANAGER_H_
