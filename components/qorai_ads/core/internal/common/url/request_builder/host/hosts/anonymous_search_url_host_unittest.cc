/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/url/request_builder/host/url_host_util.h"
#include "qorai/components/qorai_ads/core/internal/global_state/global_state.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsAnonymousSearchUrlHostTest : public test::TestBase {};

TEST_F(QoraiAdsAnonymousSearchUrlHostTest, GetProductionUrlHost) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->Flags().environment_type =
      mojom::EnvironmentType::kProduction;

  // Act & Assert
  EXPECT_EQ("https://search.anonymous.ads.qorai.com",
            GetAnonymousSearchUrlHost());
}

TEST_F(QoraiAdsAnonymousSearchUrlHostTest, GetStagingUrlHost) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());
  GlobalState::GetInstance()->Flags().environment_type =
      mojom::EnvironmentType::kStaging;

  // Act & Assert
  EXPECT_EQ("https://search.anonymous.ads.qoraisoftware.com",
            GetAnonymousSearchUrlHost());
}

}  // namespace qorai_ads
