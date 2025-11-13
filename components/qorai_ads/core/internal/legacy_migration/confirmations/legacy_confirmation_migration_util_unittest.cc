/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/legacy_migration/confirmations/legacy_confirmation_migration_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsLegacyConfirmationMigrationUtilTest : public test::TestBase {};

TEST_F(QoraiAdsLegacyConfirmationMigrationUtilTest, HasMigrated) {
  // Arrange
  test::SetProfileBooleanPrefValue(prefs::kHasMigratedConfirmationState, true);

  // Act & Assert
  EXPECT_TRUE(HasMigratedConfirmation());
}

TEST_F(QoraiAdsLegacyConfirmationMigrationUtilTest, HasNotMigrated) {
  // Arrange
  test::SetProfileBooleanPrefValue(prefs::kHasMigratedConfirmationState, false);

  // Act & Assert
  EXPECT_FALSE(HasMigratedConfirmation());
}

}  // namespace qorai_ads
