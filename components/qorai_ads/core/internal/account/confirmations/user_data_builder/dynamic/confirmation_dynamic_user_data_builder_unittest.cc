/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/confirmations/user_data_builder/dynamic/confirmation_dynamic_user_data_builder.h"

#include "base/test/values_test_util.h"
#include "qorai/components/qorai_ads/core/internal/account/confirmations/user_data_builder/confirmation_user_data_builder_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsConfirmationDynamicUserDataBuilderTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    test::MockConfirmationUserData();

    AdvanceClockTo(test::TimeFromUTCString("November 18 2020 12:34:56.789"));
  }
};

TEST_F(QoraiAdsConfirmationDynamicUserDataBuilderTest, BuildDynamicUserData) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "diagnosticId": "c1298fde-7fdb-401f-a3ce-0b58fe86e6e2",
                      "systemTimestamp": "2020-11-18T12:00:00.000Z"
                    })JSON"),
            BuildDynamicUserData());
}

TEST_F(QoraiAdsConfirmationDynamicUserDataBuilderTest,
       DoNotBuildDynamicUserDataForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  EXPECT_THAT(BuildDynamicUserData(), ::testing::IsEmpty());
}

}  // namespace qorai_ads
