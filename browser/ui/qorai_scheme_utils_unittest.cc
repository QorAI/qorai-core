// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/qorai_scheme_utils.h"

#include "testing/gtest/include/gtest/gtest.h"

TEST(QoraiSchemeUtilsTest, ReplaceChromeToQoraiScheme) {
  std::u16string url_string = u"chrome://settings";
  EXPECT_TRUE(qorai_utils::ReplaceChromeToQoraiScheme(url_string));
  EXPECT_EQ(url_string, u"qorai://settings");

  url_string = u"chrome://flags";
  EXPECT_TRUE(qorai_utils::ReplaceChromeToQoraiScheme(url_string));
  EXPECT_EQ(url_string, u"qorai://flags");

  url_string = u"https://search.qorai.com";
  EXPECT_FALSE(qorai_utils::ReplaceChromeToQoraiScheme(url_string));
  EXPECT_EQ(url_string, u"https://search.qorai.com");
}
