/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_data/fixed/studies_user_data.h"

#include "base/metrics/field_trial.h"
#include "base/test/values_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsStudiesUserDataTest : public test::TestBase {};

TEST_F(QoraiAdsStudiesUserDataTest, BuildStudiesUserDataIfNoFieldTrials) {
  // Arrange
  ASSERT_EQ(0U, base::FieldTrialList::GetFieldTrialCount());

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "studies": []
                    })JSON"),
            BuildStudiesUserData());
}

TEST_F(QoraiAdsStudiesUserDataTest, BuildStudiesUserDataForSingleFieldTrial) {
  // Arrange
  const scoped_refptr<base::FieldTrial> field_trial =
      base::FieldTrialList::CreateFieldTrial("QoraiAds.FooStudy", "GroupA");
  ASSERT_EQ("GroupA", field_trial->group_name());
  ASSERT_EQ(1U, base::FieldTrialList::GetFieldTrialCount());

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "studies": [
                        {
                          "group": "GroupA",
                          "name": "QoraiAds.FooStudy"
                        }
                      ]
                    }
                )JSON"),
            BuildStudiesUserData());
}

TEST_F(QoraiAdsStudiesUserDataTest,
       DoNotBuildStudiesUserDataForMultipleFieldTrials) {
  // Arrange
  const scoped_refptr<base::FieldTrial> field_trial_1 =
      base::FieldTrialList::CreateFieldTrial("QoraiAds.FooStudy", "GroupA");
  ASSERT_EQ("GroupA", field_trial_1->group_name());

  const scoped_refptr<base::FieldTrial> field_trial_2 =
      base::FieldTrialList::CreateFieldTrial("QoraiAds.BarStudy", "GroupB");
  ASSERT_EQ("GroupB", field_trial_2->group_name());

  ASSERT_EQ(2U, base::FieldTrialList::GetFieldTrialCount());

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "studies": []
                    })JSON"),
            BuildStudiesUserData());
}

TEST_F(QoraiAdsStudiesUserDataTest,
       DoNotBuildStudiesUserDataForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  const scoped_refptr<base::FieldTrial> field_trial =
      base::FieldTrialList::CreateFieldTrial("QoraiAds.FooStudy", "GroupA");
  ASSERT_EQ("GroupA", field_trial->group_name());
  ASSERT_EQ(1U, base::FieldTrialList::GetFieldTrialCount());

  // Act & Assert
  EXPECT_THAT(BuildStudiesUserData(), ::testing::IsEmpty());
}

}  // namespace qorai_ads
