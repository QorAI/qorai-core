/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UPHOLD_UPHOLD_USER_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UPHOLD_UPHOLD_USER_H_

#include <string>

namespace qorai_rewards::internal::uphold {

struct User {
  User();

  User(const User&);
  User& operator=(const User&);

  std::string name;
  std::string member_id;
  std::string country_id;
  bool qor_not_allowed = true;
};

}  // namespace qorai_rewards::internal::uphold

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_ENGINE_UPHOLD_UPHOLD_USER_H_
