/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/types/verifiable_conversion/id_pattern/parsers/verifiable_conversion_id_html_parser_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversions_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/resource/conversion_resource_id_pattern_info.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/resource/conversion_resource_id_pattern_search_in_types.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

namespace {

constexpr char kMatchingHtml[] =
    R"(<html><div style="foo" id="xyzzy-id" class="bar">waldo</div></html>)";
constexpr char kMismatchingHtml[] =
    R"(<html><div style="foo" id="qux" class="bar">waldo</div></html>)";

constexpr char kIdPattern[] = R"(<div.*id="xyzzy-id".*>(.*)</div>)";

}  // namespace

class QoraiAdsVerifiableConversionIdHtmlParserUtilTest : public test::TestBase {
};

TEST_F(QoraiAdsVerifiableConversionIdHtmlParserUtilTest,
       ParseVerifableConversionIdFromHtml) {
  // Act & Assert
  EXPECT_EQ("waldo", MaybeParseVerifableConversionIdFromHtml(
                         kMatchingHtml,
                         ConversionResourceIdPatternInfo{
                             test::kMatchingUrlPattern,
                             ConversionResourceIdPatternSearchInType::kHtml,
                             kIdPattern}));
}

TEST_F(QoraiAdsVerifiableConversionIdHtmlParserUtilTest,
       DoNotParseMismatchingVerifableConversionIdFromHtml) {
  // Act & Assert
  EXPECT_FALSE(MaybeParseVerifableConversionIdFromHtml(
      kMismatchingHtml,
      ConversionResourceIdPatternInfo{
          test::kMatchingUrlPattern,
          ConversionResourceIdPatternSearchInType::kHtml, kIdPattern}));
}

TEST_F(QoraiAdsVerifiableConversionIdHtmlParserUtilTest,
       DoNotParseVerifableConversionIdFromEmptyHtml) {
  // Act & Assert
  EXPECT_FALSE(MaybeParseVerifableConversionIdFromHtml(
      /*html=*/"",
      ConversionResourceIdPatternInfo{
          test::kMatchingUrlPattern,
          ConversionResourceIdPatternSearchInType::kHtml, kIdPattern}));
}

}  // namespace qorai_ads
