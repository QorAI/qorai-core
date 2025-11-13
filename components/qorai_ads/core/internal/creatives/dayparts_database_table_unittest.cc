/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/creatives/dayparts_database_table.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads::database::table {

TEST(QoraiAdsDayPartsDatabaseTableTest, GetTableName) {
  // Arrange
  const Dayparts database_table;

  // Act & Assert
  EXPECT_EQ("dayparts", database_table.GetTableName());
}

}  // namespace qorai_ads::database::table
