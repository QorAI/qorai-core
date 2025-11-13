/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/legacy_migration/client/legacy_client_migration_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsLegacyClientMigrationUtilTest : public test::TestBase {};

TEST_F(QoraiAdsLegacyClientMigrationUtilTest, HasMigrated) {
  // Arrange
  test::SetProfileBooleanPrefValue(prefs::kHasMigratedClientState, true);

  // Act & Assert
  EXPECT_TRUE(HasMigratedClientState());
}

TEST_F(QoraiAdsLegacyClientMigrationUtilTest, HasNotMigrated) {
  // Arrange
  test::SetProfileBooleanPrefValue(prefs::kHasMigratedClientState, false);

  // Act & Assert
  EXPECT_FALSE(HasMigratedClientState());
}

}  // namespace qorai_ads
