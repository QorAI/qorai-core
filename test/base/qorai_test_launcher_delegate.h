/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_TEST_BASE_QORAI_TEST_LAUNCHER_DELEGATE_H_
#define QORAI_TEST_BASE_QORAI_TEST_LAUNCHER_DELEGATE_H_

#include "build/build_config.h"
#include "chrome/test/base/chrome_test_launcher.h"

class QoraiTestLauncherDelegate : public ChromeTestLauncherDelegate {
 public:
  // Does not take ownership of ChromeTestSuiteRunner.
  explicit QoraiTestLauncherDelegate(ChromeTestSuiteRunner* runner);
  QoraiTestLauncherDelegate(const QoraiTestLauncherDelegate&) = delete;
  QoraiTestLauncherDelegate& operator=(const QoraiTestLauncherDelegate&) =
      delete;
  ~QoraiTestLauncherDelegate() override;
};

#endif  // QORAI_TEST_BASE_QORAI_TEST_LAUNCHER_DELEGATE_H_
