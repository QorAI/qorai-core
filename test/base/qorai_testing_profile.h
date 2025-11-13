/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_TEST_BASE_QORAI_TESTING_PROFILE_H_
#define QORAI_TEST_BASE_QORAI_TESTING_PROFILE_H_

#include "chrome/test/base/testing_profile.h"

class QoraiTestingProfile : public TestingProfile {
 public:
  QoraiTestingProfile();
  QoraiTestingProfile(const base::FilePath& path,
                      Delegate* delegate,
                      CreateMode create_mode);
  ~QoraiTestingProfile() override = default;
};

#endif  // QORAI_TEST_BASE_QORAI_TESTING_PROFILE_H_
