/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/url/request_builder/host/url_host_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/global_state/global_state.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsUrlHostUtilTest : public test::TestBase {};

TEST_F(QoraiAdsUrlHostUtilTest, GetStaticUrlHost) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->Flags().environment_type =
      mojom::EnvironmentType::kProduction;

  // Act & Assert
  EXPECT_EQ("https://static.ads.qorai.com", GetStaticUrlHost());
}

TEST_F(QoraiAdsUrlHostUtilTest, GetGeoUrlHost) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->Flags().environment_type =
      mojom::EnvironmentType::kProduction;

  // Act & Assert
  EXPECT_EQ("https://geo.ads.qorai.com", GetGeoUrlHost());
}

TEST_F(QoraiAdsUrlHostUtilTest, GetNonAnonymousUrlHost) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->Flags().environment_type =
      mojom::EnvironmentType::kProduction;

  // Act & Assert
  EXPECT_EQ("https://mywallet.ads.qorai.com", GetNonAnonymousUrlHost());
}

TEST_F(QoraiAdsUrlHostUtilTest, GetAnonymousUrlHost) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->Flags().environment_type =
      mojom::EnvironmentType::kProduction;

  // Act & Assert
  EXPECT_EQ("https://anonymous.ads.qorai.com", GetAnonymousUrlHost());
}

TEST_F(QoraiAdsUrlHostUtilTest, GetAnonymousSearchUrlHost) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->Flags().environment_type =
      mojom::EnvironmentType::kProduction;

  // Act & Assert
  EXPECT_EQ("https://search.anonymous.ads.qorai.com",
            GetAnonymousSearchUrlHost());
}

}  // namespace qorai_ads
