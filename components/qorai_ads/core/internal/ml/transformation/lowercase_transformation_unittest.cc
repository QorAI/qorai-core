/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/ml/transformation/lowercase_transformation.h"

#include <vector>

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/ml/data/text_data.h"
#include "qorai/components/qorai_ads/core/internal/ml/data/vector_data.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads::ml {

class QoraiAdsLowercaseTransformationTest : public test::TestBase {};

TEST_F(QoraiAdsLowercaseTransformationTest, WrongInputDataTest) {
  // Arrange
  const std::unique_ptr<Data> vector_data =
      std::make_unique<VectorData>(std::vector<float>(1.0F));

  const LowercaseTransformation lowercase;

  // Act
  const std::unique_ptr<Data> output_data = lowercase.Apply(vector_data);

  // Assert
  EXPECT_FALSE(output_data.get());
}

TEST_F(QoraiAdsLowercaseTransformationTest, LowercaseTest) {
  // Arrange
  constexpr char kUppercaseText[] = "LOWER CASE";
  constexpr char kLowercaseText[] = "lower case";
  const std::unique_ptr<Data> uppercase_data =
      std::make_unique<TextData>(kUppercaseText);

  const LowercaseTransformation lowercase;

  // Act
  const std::unique_ptr<Data> lowercase_data = lowercase.Apply(uppercase_data);

  ASSERT_EQ(DataType::kText, lowercase_data->GetType());
  const TextData* const lowercase_text_data =
      static_cast<TextData*>(lowercase_data.get());

  // Assert
  EXPECT_EQ(kLowercaseText, lowercase_text_data->GetText());
}

}  // namespace qorai_ads::ml
