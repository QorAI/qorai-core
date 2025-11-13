/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_data/fixed/version_number_user_data.h"

#include "base/test/values_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsVersionNumberUserDataTest : public test::TestBase {};

TEST_F(QoraiAdsVersionNumberUserDataTest, BuildVersionNumberUserData) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "versionNumber": "1.2.3.4"
                    })JSON"),
            BuildVersionNumberUserData());
}

TEST_F(QoraiAdsVersionNumberUserDataTest,
       DoNotBuildVersionNumberUserDataForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  EXPECT_THAT(BuildVersionNumberUserData(), ::testing::IsEmpty());
}

}  // namespace qorai_ads
