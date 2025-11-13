/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_TEST_BASE_CHROME_TEST_LAUNCHER_H_
#define QORAI_CHROMIUM_SRC_CHROME_TEST_BASE_CHROME_TEST_LAUNCHER_H_
#include "qorai/app/qorai_main_delegate.h"

#define ChromeMainDelegate QoraiMainDelegate
#include <chrome/test/base/chrome_test_launcher.h>  // IWYU pragma: export
#undef ChromeMainDelegate

#endif  // QORAI_CHROMIUM_SRC_CHROME_TEST_BASE_CHROME_TEST_LAUNCHER_H_
