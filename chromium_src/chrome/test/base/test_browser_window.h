/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_TEST_BASE_TEST_BROWSER_WINDOW_H_
#define QORAI_CHROMIUM_SRC_CHROME_TEST_BASE_TEST_BROWSER_WINDOW_H_

#include "qorai/browser/ui/qorai_browser_window.h"

#define BrowserWindow QoraiBrowserWindow
#include <chrome/test/base/test_browser_window.h>  // IWYU pragma: export
#undef BrowserWindow

#endif  // QORAI_CHROMIUM_SRC_CHROME_TEST_BASE_TEST_BROWSER_WINDOW_H_
