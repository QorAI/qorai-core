/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_SESSION_CRASHED_BUBBLE_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_SESSION_CRASHED_BUBBLE_H_

#define ShowIfNotOffTheRecordProfile                                 \
  ShowIfNotOffTheRecordProfileQorai(BrowserWindowInterface* browser, \
                                    bool skip_tab_checking);         \
  static void ShowIfNotOffTheRecordProfile

#include <chrome/browser/ui/session_crashed_bubble.h>  // IWYU pragma: export

#undef ShowIfNotOffTheRecordProfile

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_SESSION_CRASHED_BUBBLE_H_
