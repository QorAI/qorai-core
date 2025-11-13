/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/legacy_migration/legacy_migration.h"

#include "base/test/mock_callback.h"
#include "qorai/components/qorai_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/legacy_migration/legacy_migration_util.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsLegacyMigrationTest : public test::TestBase {};

TEST_F(QoraiAdsLegacyMigrationTest, Migrate) {
  // Arrange
  test::SetProfileBooleanPrefValue(prefs::kHasMigratedState, false);

  // Act & Assert
  base::MockCallback<InitializeCallback> callback;
  EXPECT_CALL(callback, Run(/*success=*/true));
  MigrateState(callback.Get());

  EXPECT_TRUE(HasMigratedState());
}

TEST_F(QoraiAdsLegacyMigrationTest, AlreadyMigrated) {
  // Arrange
  test::SetProfileBooleanPrefValue(prefs::kHasMigratedState, true);

  // Act & Assert
  base::MockCallback<InitializeCallback> callback;
  EXPECT_CALL(callback, Run(/*success=*/true));
  MigrateState(callback.Get());

  EXPECT_TRUE(HasMigratedState());
}

}  // namespace qorai_ads
