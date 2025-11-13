/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/diagnostics/entries/catalog_id_diagnostic_entry.h"

#include "qorai/components/qorai_ads/core/internal/catalog/catalog_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/catalog/catalog_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/diagnostics/diagnostic_entry_types.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds.*

namespace qorai_ads {

class QoraiAdsCatalogIdDiagnosticEntryTest : public test::TestBase {};

TEST_F(QoraiAdsCatalogIdDiagnosticEntryTest, CatalogId) {
  // Arrange
  SetCatalogId(test::kCatalogId);

  const CatalogIdDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kCatalogId, diagnostic_entry.GetType());
  EXPECT_EQ("Catalog ID", diagnostic_entry.GetName());
  EXPECT_EQ(test::kCatalogId, diagnostic_entry.GetValue());
}

TEST_F(QoraiAdsCatalogIdDiagnosticEntryTest, EmptyCatalogId) {
  // Arrange
  const CatalogIdDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kCatalogId, diagnostic_entry.GetType());
  EXPECT_EQ("Catalog ID", diagnostic_entry.GetName());
  EXPECT_THAT(diagnostic_entry.GetValue(), ::testing::IsEmpty());
}

}  // namespace qorai_ads
