/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_TEST_BASE_QORAI_UNIT_TEST_SUITE_H_
#define QORAI_TEST_BASE_QORAI_UNIT_TEST_SUITE_H_

#include <memory>

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/test/test_discardable_memory_allocator.h"
#include "chrome/test/base/chrome_unit_test_suite.h"

class QoraiUnitTestSuite : public ChromeUnitTestSuite {
 public:
  QoraiUnitTestSuite(int argc, char** argv);
  QoraiUnitTestSuite(const QoraiUnitTestSuite&) = delete;
  QoraiUnitTestSuite& operator=(const QoraiUnitTestSuite&) = delete;

 protected:
  // base::TestSuite overrides:
  void Initialize() override;
};

#endif  // QORAI_TEST_BASE_QORAI_UNIT_TEST_SUITE_H_
