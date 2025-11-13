/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_data/dynamic/diagnostic_id_user_data.h"

#include "base/test/values_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_constants.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsDiagnosticIdUserDataTest : public test::TestBase {};

TEST_F(QoraiAdsDiagnosticIdUserDataTest, BuildDiagnosticIdUserData) {
  // Arrange
  test::SetProfileStringPrefValue(prefs::kDiagnosticId, test::kDiagnosticId);

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "diagnosticId": "c1298fde-7fdb-401f-a3ce-0b58fe86e6e2"
                    })JSON"),
            BuildDiagnosticIdUserData());
}

TEST_F(QoraiAdsDiagnosticIdUserDataTest,
       DoNotBuildDiagnosticIdUserDataForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  test::SetProfileStringPrefValue(prefs::kDiagnosticId, test::kDiagnosticId);

  // Act & Assert
  EXPECT_THAT(BuildDiagnosticIdUserData(), ::testing::IsEmpty());
}

TEST_F(QoraiAdsDiagnosticIdUserDataTest,
       DoNotBuildDiagnosticUserDataIfDiagnosticIdIsInvalid) {
  // Arrange
  test::SetProfileStringPrefValue(prefs::kDiagnosticId, "INVALID");

  // Act & Assert
  EXPECT_THAT(BuildDiagnosticIdUserData(), ::testing::IsEmpty());
}

TEST_F(QoraiAdsDiagnosticIdUserDataTest,
       DoNotBuildDiagnosticIdUserDataIfDiagnosticIdIsEmpty) {
  // Arrange
  test::SetProfileStringPrefValue(prefs::kDiagnosticId, "");

  // Act & Assert
  EXPECT_THAT(BuildDiagnosticIdUserData(), ::testing::IsEmpty());
}

}  // namespace qorai_ads
