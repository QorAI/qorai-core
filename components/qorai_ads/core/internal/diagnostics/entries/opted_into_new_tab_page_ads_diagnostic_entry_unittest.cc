/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/diagnostics/entries/opted_into_new_tab_page_ads_diagnostic_entry.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/diagnostics/diagnostic_entry_types.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds.*

namespace qorai_ads {

class QoraiAdsOptedInToNewTabPageAdsDiagnosticEntryTest
    : public test::TestBase {};

TEST_F(QoraiAdsOptedInToNewTabPageAdsDiagnosticEntryTest, IsOptedIn) {
  // Arrange
  const OptedInToNewTabPageAdsDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kOptedInToNewTabPageAds,
            diagnostic_entry.GetType());
  EXPECT_EQ("Opted into new tab page ads", diagnostic_entry.GetName());
  EXPECT_EQ("true", diagnostic_entry.GetValue());
}

TEST_F(QoraiAdsOptedInToNewTabPageAdsDiagnosticEntryTest, IsOptedOut) {
  // Arrange
  test::OptOutOfNewTabPageAds();

  const OptedInToNewTabPageAdsDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kOptedInToNewTabPageAds,
            diagnostic_entry.GetType());
  EXPECT_EQ("Opted into new tab page ads", diagnostic_entry.GetName());
  EXPECT_EQ("false", diagnostic_entry.GetValue());
}

}  // namespace qorai_ads
