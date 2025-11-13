/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/test/base/testing_browser_process.h"

#include "qorai/test/base/testing_qorai_browser_process.h"

// These overrides are used to make sure a TestingQoraiBrowserProcess instance
// has a its life time matching the one for the global instance of
// `TestingQoraiBrowserProcess`. Therefore, we override all the methods involved
// with creating and destroying the upstream instance.
#define QORAI_TESTING_BROWSER_PROCESS_CREATE_INSTANCE \
  TestingQoraiBrowserProcess::CreateInstance();
#define QORAI_TESTING_BROWSER_PROCESS_DELETE_INSTANCE \
  TestingQoraiBrowserProcess::DeleteInstance();
#define QORAI_TESTING_BROWSER_PROCESS_TEAR_DOWN_AND_DELETE_INSTANCE \
  TestingQoraiBrowserProcess::TearDownAndDeleteInstance();

#include <chrome/test/base/testing_browser_process.cc>

#undef QORAI_TESTING_BROWSER_PROCESS_CREATE_INSTANCE
#undef QORAI_TESTING_BROWSER_PROCESS_DELETE_INSTANCE
#undef QORAI_TESTING_BROWSER_PROCESS_TEAR_DOWN_AND_DELETE_INSTANCE
