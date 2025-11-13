/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/targeting/user_model/interest/interest_segments.h"

#include <memory>

#include "base/test/mock_callback.h"
#include "base/test/scoped_feature_list.h"
#include "qorai/components/qorai_ads/core/internal/common/resources/language_components_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/segments/segment_alias.h"
#include "qorai/components/qorai_ads/core/internal/serving/targeting/user_model/interest/interest_user_model_info.h"
#include "qorai/components/qorai_ads/core/internal/targeting/contextual/text_classification/text_classification_feature.h"
#include "qorai/components/qorai_ads/core/internal/targeting/targeting_test_helper.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsInterestSegmentsTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    targeting_helper_ =
        std::make_unique<test::TargetingHelper>(task_environment_);

    NotifyResourceComponentDidChange(test::kLanguageComponentManifestVersion,
                                     test::kLanguageComponentId);
  }

  std::unique_ptr<test::TargetingHelper> targeting_helper_;
};

TEST_F(QoraiAdsInterestSegmentsTest, BuildInterestSegments) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kTextClassificationFeature);

  targeting_helper_->MockInterest();

  // Act & Assert
  base::MockCallback<BuildSegmentsCallback> callback;
  EXPECT_CALL(callback,
              Run(test::TargetingHelper::InterestExpectation().segments));
  BuildInterestSegments(callback.Get());
}

TEST_F(QoraiAdsInterestSegmentsTest, BuildInterestSegmentsIfNoTargeting) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kTextClassificationFeature);

  // Act & Assert
  base::MockCallback<BuildSegmentsCallback> callback;
  EXPECT_CALL(callback, Run(/*segments=*/::testing::IsEmpty()));
  BuildInterestSegments(callback.Get());
}

TEST_F(QoraiAdsInterestSegmentsTest,
       DoNotBuildInterestSegmentsIfFeatureIsDisabled) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndDisableFeature(kTextClassificationFeature);

  targeting_helper_->MockInterest();

  // Act & Assert
  base::MockCallback<BuildSegmentsCallback> callback;
  EXPECT_CALL(callback, Run(/*segments=*/::testing::IsEmpty()));
  BuildInterestSegments(callback.Get());
}

}  // namespace qorai_ads
