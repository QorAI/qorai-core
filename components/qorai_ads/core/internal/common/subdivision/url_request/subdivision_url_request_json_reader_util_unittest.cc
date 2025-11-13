/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/subdivision/url_request/subdivision_url_request_json_reader_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_constants.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads::json::reader {

TEST(QoraiAdsSubdivisionUrlRequestJsonReaderUtilTest, ParseJson) {
  // Act & Assert
  EXPECT_EQ("US-CA", ParseSubdivision(
                         R"(
                            {
                              "country": "US",
                              "region": "CA"
                            })"));
}

TEST(QoraiAdsSubdivisionUrlRequestJsonReaderUtilTest, DoNotParseMalformedJson) {
  // Act & Assert
  EXPECT_FALSE(ParseSubdivision(test::kMalformedJson));
}

TEST(QoraiAdsSubdivisionUrlRequestJsonReaderUtilTest,
     DoNotParseIfMissingCountry) {
  // Act & Assert
  EXPECT_FALSE(ParseSubdivision(
      R"(
          {
            "region": "CA"
          })"));
}

TEST(QoraiAdsSubdivisionUrlRequestJsonReaderUtilTest,
     DoNotParseifEmptyCountry) {
  // Act & Assert
  EXPECT_FALSE(ParseSubdivision(
      R"(
          {
            "country": "",
            "region": "CA"
          })"));
}

TEST(QoraiAdsSubdivisionUrlRequestJsonReaderUtilTest,
     DoNotParseIfMissingRegion) {
  // Act & Assert
  EXPECT_FALSE(ParseSubdivision(
      R"(
          {
            "country": "US"
          })"));
}

TEST(QoraiAdsSubdivisionUrlRequestJsonReaderUtilTest, DoNotParseIfEmptyRegion) {
  // Act & Assert
  EXPECT_FALSE(ParseSubdivision(
      R"(
          {
            "country": "US",
            "region": ""
          })"));
}

}  // namespace qorai_ads::json::reader
