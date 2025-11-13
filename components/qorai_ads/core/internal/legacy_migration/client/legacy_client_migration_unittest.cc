/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/legacy_migration/client/legacy_client_migration.h"

#include "base/test/mock_callback.h"
#include "qorai/components/qorai_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_constants.h"
#include "qorai/components/qorai_ads/core/internal/legacy_migration/client/legacy_client_migration_util.h"
#include "qorai/components/qorai_ads/core/public/ads_constants.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

namespace {
constexpr char kLegacyClientMigrationJsonFilename[] =
    "legacy_client_migration.json";
}  // namespace

class QoraiAdsLegacyClientMigrationTest : public test::TestBase {};

TEST_F(QoraiAdsLegacyClientMigrationTest, Migrate) {
  // Arrange
  test::SetProfileBooleanPrefValue(prefs::kHasMigratedClientState, false);

  ASSERT_TRUE(CopyFileFromTestDataPathToProfilePath(
      kLegacyClientMigrationJsonFilename));

  // Act & Assert
  base::MockCallback<InitializeCallback> callback;
  EXPECT_CALL(callback, Run(/*success=*/true));
  MigrateClientState(callback.Get());

  EXPECT_TRUE(HasMigratedClientState());
}

TEST_F(QoraiAdsLegacyClientMigrationTest, AlreadyMigrated) {
  // Arrange
  test::SetProfileBooleanPrefValue(prefs::kHasMigratedClientState, true);

  ASSERT_TRUE(CopyFileFromTestDataPathToProfilePath(kClientJsonFilename));

  // Act & Assert
  base::MockCallback<InitializeCallback> callback;
  EXPECT_CALL(callback, Run(/*success=*/true));
  MigrateClientState(callback.Get());

  EXPECT_TRUE(HasMigratedClientState());
}

TEST_F(QoraiAdsLegacyClientMigrationTest, ResetMalformedClientState) {
  // Arrange
  test::SetProfileBooleanPrefValue(prefs::kHasMigratedClientState, false);

  ASSERT_TRUE(CopyFileFromTestDataPathToProfilePath(
      test::kMalformedJsonFilename, kClientJsonFilename));

  // Act & Assert
  base::MockCallback<InitializeCallback> callback;
  EXPECT_CALL(callback, Run(/*success=*/true));
  MigrateClientState(callback.Get());

  EXPECT_TRUE(HasMigratedClientState());
}

}  // namespace qorai_ads
