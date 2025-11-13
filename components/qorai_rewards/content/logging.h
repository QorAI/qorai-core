/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CONTENT_LOGGING_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CONTENT_LOGGING_H_

#include <sstream>

namespace qorai_rewards {

#define BLOG(verbose_level, stream)      \
  Log(__FILE__, __LINE__, verbose_level, \
      (std::ostringstream() << stream).str());

#define BLOG_IF(verbose_level, condition, stream) \
  !(condition) ? (void)0 : BLOG(verbose_level, stream)

}  // namespace qorai_rewards

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CONTENT_LOGGING_H_
