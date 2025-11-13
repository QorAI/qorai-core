/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/legacy_migration/confirmations/legacy_confirmation_migration.h"

#include "base/test/mock_callback.h"
#include "qorai/components/qorai_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_constants.h"
#include "qorai/components/qorai_ads/core/internal/legacy_migration/confirmations/legacy_confirmation_migration_util.h"
#include "qorai/components/qorai_ads/core/public/ads_callback.h"
#include "qorai/components/qorai_ads/core/public/ads_constants.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsLegacyConfirmationMigrationTest : public test::TestBase {
 protected:
  void SetUpMocks() override {
    test::SetProfileBooleanPrefValue(prefs::kHasMigratedConfirmationState,
                                     false);
  }
};

TEST_F(QoraiAdsLegacyConfirmationMigrationTest, Migrate) {
  // Arrange
  ASSERT_TRUE(
      CopyFileFromTestDataPathToProfilePath(kConfirmationsJsonFilename));

  // Act & Assert
  base::MockCallback<InitializeCallback> callback;
  EXPECT_CALL(callback, Run(/*success=*/true));
  MigrateConfirmationState(callback.Get());

  EXPECT_TRUE(HasMigratedConfirmation());
}

TEST_F(QoraiAdsLegacyConfirmationMigrationTest, ResetMalformedState) {
  // Arrange
  ASSERT_TRUE(CopyFileFromTestDataPathToProfilePath(
      test::kMalformedJsonFilename, kConfirmationsJsonFilename));

  // Act & Assert
  base::MockCallback<InitializeCallback> callback;
  EXPECT_CALL(callback, Run(/*success=*/true));
  MigrateConfirmationState(callback.Get());

  EXPECT_TRUE(HasMigratedConfirmation());
}

}  // namespace qorai_ads
