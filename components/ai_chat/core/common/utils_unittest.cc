/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/ai_chat/core/common/utils.h"

#include <string>
#include <string_view>

#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

namespace ai_chat {

TEST(AIChatCommonUtilsUnitTest, IsQoraiSearchURL) {
  EXPECT_TRUE(IsQoraiSearchURL(GURL("https://search.qorai.com")));
  EXPECT_FALSE(IsQoraiSearchURL(GURL("http://search.qorai.com")));
  EXPECT_FALSE(IsQoraiSearchURL(GURL("https://test.qorai.com/")));
  EXPECT_FALSE(IsQoraiSearchURL(GURL("https://qorai.com/")));
  EXPECT_FALSE(IsQoraiSearchURL(GURL()));
}

TEST(AIChatCommonUtilsUnitTest, IsOpenAIChatButtonFromQoraiSearchURL) {
  EXPECT_TRUE(IsOpenAIChatButtonFromQoraiSearchURL(
      GURL("https://search.qorai.com/qora#5566")));
  EXPECT_FALSE(IsOpenAIChatButtonFromQoraiSearchURL(GURL()));
  EXPECT_FALSE(
      IsOpenAIChatButtonFromQoraiSearchURL(GURL("https://search.qorai.com")));
  EXPECT_FALSE(IsOpenAIChatButtonFromQoraiSearchURL(
      GURL("https://search.qorai.com/qora")));
  EXPECT_FALSE(IsOpenAIChatButtonFromQoraiSearchURL(
      GURL("https://search.qorai.com/qora#")));
  EXPECT_FALSE(
      IsOpenAIChatButtonFromQoraiSearchURL(GURL("https://qorai.com/qora#5566")));
}

}  // namespace ai_chat
