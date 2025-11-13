/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_search/common/qorai_search_utils.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

namespace qorai_search {

TEST(QoraiSearchUtilsUnitTest, IsAllowedHost) {
  EXPECT_TRUE(IsAllowedHost(GURL("https://safesearch.qorai.com")));
  EXPECT_TRUE(IsAllowedHost(GURL("https://safesearch.qoraisoftware.com")));
  EXPECT_TRUE(IsAllowedHost(GURL("https://search-dev-local.qorai.com")));
  EXPECT_TRUE(IsAllowedHost(GURL("https://search.qorai.com")));
  EXPECT_TRUE(IsAllowedHost(GURL("https://search.qorai.software")));
  EXPECT_TRUE(IsAllowedHost(GURL("https://search.qoraisoftware.com")));

  // not https
  EXPECT_FALSE(IsAllowedHost(GURL("http://safesearch.qorai.com")));
  // not allowed domains
  EXPECT_FALSE(IsAllowedHost(GURL("https://earch.qorai.com")));
  EXPECT_FALSE(IsAllowedHost(GURL("https://qorai.com")));
  EXPECT_FALSE(IsAllowedHost(GURL("https://a.search.qorai.com")));
  EXPECT_FALSE(IsAllowedHost(GURL("https://search.qorai.com.au")));
}

}  // namespace qorai_search
