/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_data/fixed/page_land_user_data.h"

#include "base/test/values_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "net/http/http_status_code.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsPageLandUserDataTest : public test::TestBase {};

TEST_F(QoraiAdsPageLandUserDataTest,
       BuildPageLandUserDataForHttpInformationalResponseStatusCodeClass) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "httpResponseStatus": "1xx"
                    })JSON"),
            BuildPageLandUserData(net::HTTP_SWITCHING_PROTOCOLS));
}

TEST_F(QoraiAdsPageLandUserDataTest,
       BuildPageLandUserDataForHttpSuccessfulResponseStatusCodeClass) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "httpResponseStatus": "2xx"
                    })JSON"),
            BuildPageLandUserData(net::HTTP_IM_USED));
}

TEST_F(QoraiAdsPageLandUserDataTest,
       BuildPageLandUserDataForHttpRedirectionMessageStatusCodeClass) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "httpResponseStatus": "3xx"
                    })JSON"),
            BuildPageLandUserData(net::HTTP_MOVED_PERMANENTLY));
}

TEST_F(QoraiAdsPageLandUserDataTest,
       BuildPageLandUserDataForHttpClientErrorResponseStatusCode) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "httpResponseStatus": "404"
                    })JSON"),
            BuildPageLandUserData(net::HTTP_NOT_FOUND));
}

TEST_F(QoraiAdsPageLandUserDataTest,
       BuildPageLandUserDataForHttpClientErrorResponseStatusCodeClass) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "httpResponseStatus": "4xx"
                    })JSON"),
            BuildPageLandUserData(net::HTTP_UPGRADE_REQUIRED));
}

TEST_F(
    QoraiAdsPageLandUserDataTest,
    BuildPageLandUserDataForPrivacyPreservingHttpServerErrorResponseStatusCode) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "httpResponseStatus": "500"
                    })JSON"),
            BuildPageLandUserData(net::HTTP_INTERNAL_SERVER_ERROR));
}

TEST_F(
    QoraiAdsPageLandUserDataTest,
    BuildPageLandUserDataForPrivacyPreservingHttpServerErrorResponseStatusCodeClass) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "httpResponseStatus": "5xx"
                    })JSON"),
            BuildPageLandUserData(net::HTTP_LOOP_DETECTED));
}

TEST_F(
    QoraiAdsPageLandUserDataTest,
    DoNotBuildPageLandUserDataForHttpResponseStatusErrorPageForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  EXPECT_THAT(BuildPageLandUserData(net::HTTP_NOT_FOUND), ::testing::IsEmpty());
}

}  // namespace qorai_ads
