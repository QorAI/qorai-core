/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/search_engine/search_engine_results_page_util.h"

#include "qorai/components/qorai_ads/core/internal/common/search_engine/search_engine_results_page_test_constants.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsSearchEngineResultsPageUtilTest, IsSearchEngineResultsPage) {
  // Act & Assert
  for (const auto& url : test::GetSearchEngineResultsPageUrls()) {
    EXPECT_TRUE(IsSearchEngineResultsPage(url));
  }
}

TEST(QoraiAdsSearchEngineResultsPageUtilTest, IsNotSearchEngineResultsPage) {
  // Act & Assert
  EXPECT_FALSE(IsSearchEngineResultsPage(GURL("https://qorai.com/")));
}

TEST(QoraiAdsSearchEngineResultsPageUtilTest,
     IsNotSearchEngineResultsPageWithInvalidUrl) {
  // Act & Assert
  EXPECT_FALSE(IsSearchEngineResultsPage(GURL("INVALID")));
}

TEST(QoraiAdsSearchEngineResultsPageUtilTest, ExtractSearchTermQueryValue) {
  // Act & Assert
  for (const auto& url : test::GetSearchEngineResultsPageUrls()) {
    if (std::optional<std::string> search_term_query_value =
            ExtractSearchTermQueryValue(url)) {
      EXPECT_EQ("foobar", search_term_query_value);
    }
  }
}

TEST(QoraiAdsSearchEngineResultsPageUtilTest,
     FailToExtractSearchTermQueryValueFromUrlWithMissingQuery) {
  // Act & Assert
  EXPECT_FALSE(ExtractSearchTermQueryValue(GURL("https://google.com/")));
}

TEST(QoraiAdsSearchEngineResultsPageUtilTest,
     FailToExtractSearchTermQueryValueFromInvalidUrl) {
  // Act & Assert
  EXPECT_FALSE(ExtractSearchTermQueryValue(GURL("INVALID")));
}

}  // namespace qorai_ads
