/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_data/dynamic/system_timestamp_user_data.h"

#include "base/test/values_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsSystemTimestampUserDataTest : public test::TestBase {};

TEST_F(QoraiAdsSystemTimestampUserDataTest, BuildSystemTimestampUserData) {
  // Arrange
  AdvanceClockTo(test::TimeFromUTCString("November 18 2020 12:34:56.789"));

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "systemTimestamp": "2020-11-18T12:00:00.000Z"
                    })JSON"),
            BuildSystemTimestampUserData());
}

TEST_F(QoraiAdsSystemTimestampUserDataTest,
       DoNotBuildSystemTimestampUserDataForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  EXPECT_THAT(BuildSystemTimestampUserData(), ::testing::IsEmpty());
}

}  // namespace qorai_ads
