/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_TEST_BASE_CHROME_TEST_SUITE_H_
#define QORAI_CHROMIUM_SRC_CHROME_TEST_BASE_CHROME_TEST_SUITE_H_

#include "qorai/components/qorai_shields/content/browser/qorai_shields_test_utils.h"

#define ChromeTestSuite ChromeTestSuite_ChromiumImpl
#include <chrome/test/base/chrome_test_suite.h>  // IWYU pragma: export
#undef ChromeTestSuite

class ChromeTestSuite : public ChromeTestSuite_ChromiumImpl {
 public:
  ChromeTestSuite(int argc, char** argv);
  ~ChromeTestSuite() override;

 protected:
  // base::TestSuite overrides:
  void Initialize() override;

 private:
  // Use stable farbling both in Qorai and Chromium tests.
  qorai_shields::ScopedStableFarblingTokensForTesting
      scoped_stable_farbling_tokens_{1};
};

#endif  // QORAI_CHROMIUM_SRC_CHROME_TEST_BASE_CHROME_TEST_SUITE_H_
