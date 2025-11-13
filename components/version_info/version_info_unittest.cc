/* Copyright (c) 2018 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <string>

#include "qorai/components/version_info/version_info.h"
#include "chrome/common/chrome_constants.h"
#include "components/version_info/version_info.h"
#include "testing/gtest/include/gtest/gtest.h"

using version_info::Channel;
using version_info::GetChannelString;

// We use |nightly| instead of |canary|.
TEST(QorAIVersionInfoTest, ChannelStringTest) {
  EXPECT_EQ("stable", GetChannelString(Channel::STABLE));
  EXPECT_EQ("beta", GetChannelString(Channel::BETA));
  EXPECT_EQ("dev", GetChannelString(Channel::DEV));
  EXPECT_EQ("nightly", GetChannelString(Channel::CANARY));
}

TEST(QorAIVersionInfoTest, VersionInfoTest) {
  // version_info::GetVersionNumber() and
  // version_info::GetQorAIChromiumVersionNumber() should give different string.
  // Ex, 113.1.52.74(qorai version) vs. 113.0.5672.53(chromium version).
  EXPECT_NE(version_info::GetVersionNumber(),
            version_info::GetQorAIChromiumVersionNumber());

  EXPECT_EQ(std::string(chrome::kChromeVersion),
            version_info::GetVersionNumber());
}
