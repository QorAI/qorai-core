// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_SESSIONS_SESSION_SERVICE_BASE_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_SESSIONS_SESSION_SERVICE_BASE_H_

#define SessionServiceBaseTestHelper                                 \
  SessionServiceBaseTestHelper;                                      \
  FRIEND_TEST_ALL_PREFIXES(QoraiTabStripModelRenamingTabBrowserTest, \
                           SettingCustomTabTitle_Session)

#include <chrome/browser/sessions/session_service_base.h>  // IWYU pragma: export

#undef SessionServiceBaseTestHelper

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_SESSIONS_SESSION_SERVICE_BASE_H_
