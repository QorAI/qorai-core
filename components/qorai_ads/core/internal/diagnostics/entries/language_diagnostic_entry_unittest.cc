/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/diagnostics/entries/language_diagnostic_entry.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/diagnostics/diagnostic_entry_types.h"
#include "qorai/components/qorai_ads/core/public/common/locale/scoped_locale_for_testing.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds.*

namespace qorai_ads {

class QoraiAdsLanguageDiagnosticEntryTest : public test::TestBase {};

TEST_F(QoraiAdsLanguageDiagnosticEntryTest, GetValue) {
  // Arrange
  const test::ScopedCurrentLanguageCode scoped_current_language_code{"en"};

  const LanguageDiagnosticEntry diagnostic_entry;

  // Act & Assert
  EXPECT_EQ(DiagnosticEntryType::kLanguage, diagnostic_entry.GetType());
  EXPECT_EQ("Language", diagnostic_entry.GetName());
  EXPECT_EQ("en", diagnostic_entry.GetValue());
}

}  // namespace qorai_ads
