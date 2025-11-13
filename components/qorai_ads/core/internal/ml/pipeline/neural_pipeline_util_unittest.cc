/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/ml/pipeline/neural_pipeline_util.h"

#include <string>

#include "qorai/components/qorai_ads/core/internal/common/test/file_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/ml/pipeline/pipeline_info.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads::ml {

namespace {
constexpr char kOnlyRequiredFieldsNeuralModelPipeline[] =
    "ml/pipeline/text_processing/neural/only_required_fields_neural_model.fb";
}  // namespace

class QoraiAdsNeuralPipelineUtilTest : public test::TestBase {};

TEST_F(QoraiAdsNeuralPipelineUtilTest, LoadNeuralPipelineTest) {
  // Arrange
  std::optional<std::string> contents =
      test::MaybeReadFileToString(kOnlyRequiredFieldsNeuralModelPipeline);
  ASSERT_TRUE(contents);

  // Act
  std::optional<pipeline::PipelineInfo> pipeline = pipeline::LoadNeuralPipeline(
      reinterpret_cast<const uint8_t*>(contents->data()), contents->size());

  // Assert
  EXPECT_TRUE(pipeline);
}

}  // namespace qorai_ads::ml
