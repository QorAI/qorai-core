/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/catalog/catalog_util.h"

#include "base/test/gmock_callback_support.h"
#include "base/test/mock_callback.h"
#include "qorai/components/qorai_ads/core/internal/catalog/catalog_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"
#include "qorai/components/qorai_ads/core/internal/prefs/pref_util.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsCatalogUtilTest : public test::TestBase {};

TEST_F(QoraiAdsCatalogUtilTest, ResetCatalog) {
  // Arrange
  SetCatalogId(test::kCatalogId);
  SetCatalogVersion(1);
  SetCatalogPing(base::Hours(1));
  SetCatalogLastUpdated(test::Now());

  // Act
  base::RunLoop run_loop;
  base::MockCallback<ResultCallback> callback;
  EXPECT_CALL(callback, Run(/*success=*/true))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  ResetCatalog(callback.Get());
  run_loop.Run();

  // Assert
  EXPECT_THAT(GetProfileStringPref(prefs::kCatalogId), ::testing::IsEmpty());
  EXPECT_EQ(0, GetProfileIntegerPref(prefs::kCatalogVersion));
  EXPECT_EQ(7'200'000, GetProfileInt64Pref(prefs::kCatalogPing));
  EXPECT_TRUE(GetProfileTimePref(prefs::kCatalogLastUpdated).is_null());
}

TEST_F(QoraiAdsCatalogUtilTest, CatalogExists) {
  // Arrange
  SetCatalogVersion(1);

  // Act & Assert
  EXPECT_TRUE(DoesCatalogExist());
}

TEST_F(QoraiAdsCatalogUtilTest, CatalogDoesNotExist) {
  // Arrange
  SetCatalogVersion(0);

  // Act & Assert
  EXPECT_FALSE(DoesCatalogExist());
}

TEST_F(QoraiAdsCatalogUtilTest, CatalogHasChanged) {
  // Arrange
  SetCatalogId(test::kCatalogId);

  // Act & Assert
  EXPECT_TRUE(HasCatalogChanged(
      /*catalog_id=*/"150a9518-4db8-4fba-b104-0c420a1d9c0c"));
}

TEST_F(QoraiAdsCatalogUtilTest, CatalogHasNotChanged) {
  // Arrange
  SetCatalogId(test::kCatalogId);

  // Act & Assert
  EXPECT_FALSE(HasCatalogChanged(test::kCatalogId));
}

TEST_F(QoraiAdsCatalogUtilTest, CatalogHasExpired) {
  // Arrange
  SetCatalogLastUpdated(test::Now());

  AdvanceClockBy(base::Days(1));

  // Act & Assert
  EXPECT_TRUE(HasCatalogExpired());
}

TEST_F(QoraiAdsCatalogUtilTest, CatalogHasNotExpired) {
  // Arrange
  SetCatalogLastUpdated(test::Now());

  AdvanceClockBy(base::Days(1) - base::Milliseconds(1));

  // Act & Assert
  EXPECT_FALSE(HasCatalogExpired());
}

}  // namespace qorai_ads
