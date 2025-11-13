/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CONTENT_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CONTENT_TEST_UTIL_H_

#include <memory>

#include "base/files/file_path.h"

class Profile;

namespace qorai_rewards {

std::unique_ptr<Profile> CreateQoraiRewardsProfile(const base::FilePath& path);

}  // namespace qorai_rewards

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CONTENT_TEST_UTIL_H_
