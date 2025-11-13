/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/diagnostics/entries/opted_into_qorai_news_ads_diagnostic_entry.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/diagnostics/diagnostic_entry_types.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds.*

namespace qorai_ads {

class QoraiAdsOptedInToQoraiNewsAdsDiagnosticEntryTest : public test::TestBase {
};

TEST_F(QoraiAdsOptedInToQoraiNewsAdsDiagnosticEntryTest, IsOptedIn) {
  // Arrange
  const OptedInToQoraiNewsAdsDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kOptedInToQoraiNewsAds,
            diagnostic_entry.GetType());
  EXPECT_EQ("Opted into Qorai News ads", diagnostic_entry.GetName());
  EXPECT_EQ("true", diagnostic_entry.GetValue());
}

TEST_F(QoraiAdsOptedInToQoraiNewsAdsDiagnosticEntryTest, IsOptedOut) {
  // Arrange
  test::OptOutOfQoraiNewsAds();

  const OptedInToQoraiNewsAdsDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kOptedInToQoraiNewsAds,
            diagnostic_entry.GetType());
  EXPECT_EQ("Opted into Qorai News ads", diagnostic_entry.GetName());
  EXPECT_EQ("false", diagnostic_entry.GetValue());
}

}  // namespace qorai_ads
