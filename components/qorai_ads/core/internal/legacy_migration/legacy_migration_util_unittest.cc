/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/legacy_migration/legacy_migration_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsLegacyMigrationUtilTest : public test::TestBase {};

TEST_F(QoraiAdsLegacyMigrationUtilTest, HasMigrated) {
  // Arrange
  test::SetProfileBooleanPrefValue(prefs::kHasMigratedState, true);

  // Act & Assert
  EXPECT_TRUE(HasMigratedState());
}

TEST_F(QoraiAdsLegacyMigrationUtilTest, kHasMigratedState) {
  // Arrange
  test::SetProfileBooleanPrefValue(prefs::kHasMigratedState, false);

  // Act & Assert
  EXPECT_FALSE(HasMigratedState());
}

}  // namespace qorai_ads
