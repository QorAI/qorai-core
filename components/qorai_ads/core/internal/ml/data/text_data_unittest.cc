/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/ml/data/text_data.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads::ml {

class QoraiAdsTextDataTest : public test::TestBase {};

TEST_F(QoraiAdsTextDataTest, TextDataInitialization) {
  // Arrange
  const std::string text = "The quick brown fox jumps over the lazy dog";

  // Act
  const TextData text_data(text);

  // Assert
  EXPECT_EQ(text, text_data.GetText());
}

}  // namespace qorai_ads::ml
