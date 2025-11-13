/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/types/verifiable_conversion/id_pattern/parsers/verifiable_conversion_id_html_meta_tag_parser_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsVerifiableConversionIdHtmlMetaTagParserUtilTest
    : public test::TestBase {};

TEST_F(QoraiAdsVerifiableConversionIdHtmlMetaTagParserUtilTest,
       ParseVerifableConversionIdFromHtmlMetaTag) {
  // Act & Assert
  EXPECT_EQ("fred",
            MaybeParseVerifableConversionIdFromHtmlMetaTag(
                /*html=*/R"(<meta name="ad-conversion-id" content="fred">)"));
}

TEST_F(QoraiAdsVerifiableConversionIdHtmlMetaTagParserUtilTest,
       DoNotParseMismatchingVerifableConversionIdFromEmptyHtmlMetaTag) {
  // Act & Assert
  EXPECT_FALSE(MaybeParseVerifableConversionIdFromHtmlMetaTag(
      /*html=*/R"(<meta name="foo" content="bar">)"));
}

TEST_F(QoraiAdsVerifiableConversionIdHtmlMetaTagParserUtilTest,
       DoNotParseVerifableConversionIdFromEmptyHtmlMetaTag) {
  // Act & Assert
  EXPECT_FALSE(MaybeParseVerifableConversionIdFromHtmlMetaTag(/*html=*/""));
}

}  // namespace qorai_ads
