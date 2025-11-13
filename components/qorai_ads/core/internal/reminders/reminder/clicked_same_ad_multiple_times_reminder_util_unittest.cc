/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/reminders/reminder/clicked_same_ad_multiple_times_reminder_util.h"

#include "base/test/scoped_feature_list.h"
#include "qorai/components/qorai_ads/core/internal/account/confirmations/confirmation_type_test_util.h"
#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/ads_observer_mock.h"
#include "qorai/components/qorai_ads/core/internal/ads_observer_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/history/ad_history_test_util.h"
#include "qorai/components/qorai_ads/core/internal/reminders/reminders_feature.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_ads/core/public/history/ad_history_item_info.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsClickedSameAdMultipleTimesReminderUtilTest
    : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    ads_observer_mock_ = test::MockAdsObserver();
  }

  raw_ptr<AdsObserverMock> ads_observer_mock_ = nullptr;  // Not owned.
};

TEST_F(QoraiAdsClickedSameAdMultipleTimesReminderUtilTest, ShouldRemindUser) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  // Act & Assert
  EXPECT_TRUE(ShouldRemindUser());
}

TEST_F(QoraiAdsClickedSameAdMultipleTimesReminderUtilTest,
       ShouldNotRemindUserWhenRemindersFeatureIsDisabled) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndDisableFeature(kRemindersFeature);

  // Act & Assert
  EXPECT_FALSE(ShouldRemindUser());
}

TEST_F(QoraiAdsClickedSameAdMultipleTimesReminderUtilTest,
       ShouldNotRemindUser) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kRemindersFeature, {{"remind_user_if_clicking_the_same_ad_after", "0"}});

  // Act & Assert
  EXPECT_FALSE(ShouldRemindUser());
}

TEST_F(QoraiAdsClickedSameAdMultipleTimesReminderUtilTest,
       UserClickedTheSameAdMultipleTimes) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  const AdHistoryList ad_history = test::BuildAdHistoryForSamePlacement(
      mojom::AdType::kNotificationAd,
      test::BuildConfirmationTypeForCountAndIntersperseOtherTypes(
          mojom::ConfirmationType::kClicked,
          /*count=*/kRemindUserIfClickingTheSameAdAfter.Get()),
      /*should_generate_random_uuids=*/false);

  // Act & Assert
  EXPECT_TRUE(DidUserClickTheSameAdMultipleTimes(test::kCreativeInstanceId,
                                                 ad_history));
}

TEST_F(QoraiAdsClickedSameAdMultipleTimesReminderUtilTest,
       UserDidNotClickTheSameAdMultipleTimes) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  const AdHistoryList ad_history = test::BuildAdHistoryForSamePlacement(
      mojom::AdType::kNotificationAd,
      test::BuildConfirmationTypeForCountAndIntersperseOtherTypes(
          mojom::ConfirmationType::kClicked,
          /*count=*/kRemindUserIfClickingTheSameAdAfter.Get() - 1),
      /*should_generate_random_uuids=*/false);

  // Act & Assert
  EXPECT_FALSE(DidUserClickTheSameAdMultipleTimes(test::kCreativeInstanceId,
                                                  ad_history));
}

TEST_F(QoraiAdsClickedSameAdMultipleTimesReminderUtilTest,
       UserClickedTheSameAdMultipleTimesConsecutively) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  const AdHistoryList ad_history = test::BuildAdHistoryForSamePlacement(
      mojom::AdType::kNotificationAd,
      test::BuildConfirmationTypeForCountAndIntersperseOtherTypes(
          mojom::ConfirmationType::kClicked,
          /*count=*/kRemindUserIfClickingTheSameAdAfter.Get() * 2),
      /*should_generate_random_uuids=*/false);

  // Act & Assert
  EXPECT_TRUE(DidUserClickTheSameAdMultipleTimes(test::kCreativeInstanceId,
                                                 ad_history));
}

TEST_F(QoraiAdsClickedSameAdMultipleTimesReminderUtilTest,
       UserDidNotClickTheSameAdMultipleTimesConsecutively) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  const AdHistoryList ad_history = test::BuildAdHistoryForSamePlacement(
      mojom::AdType::kNotificationAd,
      test::BuildConfirmationTypeForCountAndIntersperseOtherTypes(
          mojom::ConfirmationType::kClicked,
          /*count=*/(kRemindUserIfClickingTheSameAdAfter.Get() * 2) - 1),
      /*should_generate_random_uuids=*/false);

  // Act & Assert
  EXPECT_FALSE(DidUserClickTheSameAdMultipleTimes(test::kCreativeInstanceId,
                                                  ad_history));
}

TEST_F(QoraiAdsClickedSameAdMultipleTimesReminderUtilTest,
       UserClickedDifferentAdsMultipleTimes) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  const AdHistoryList ad_history = test::BuildAdHistoryForSamePlacement(
      mojom::AdType::kNotificationAd,
      test::BuildConfirmationTypeForCountAndIntersperseOtherTypes(
          mojom::ConfirmationType::kClicked,
          /*count=*/kRemindUserIfClickingTheSameAdAfter.Get()),
      /*should_generate_random_uuids=*/true);

  // Act & Assert
  EXPECT_FALSE(DidUserClickTheSameAdMultipleTimes(test::kCreativeInstanceId,
                                                  ad_history));
}

TEST_F(QoraiAdsClickedSameAdMultipleTimesReminderUtilTest,
       RemindUserTheyDoNotNeedToClickToEarnRewards) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  // Act & Assert
  EXPECT_CALL(*ads_observer_mock_,
              OnRemindUser(mojom::ReminderType::kClickedSameAdMultipleTimes));
  RemindUserTheyDoNotNeedToClickToEarnRewards();
}

TEST_F(QoraiAdsClickedSameAdMultipleTimesReminderUtilTest,
       RemindUserMultipleTimesTheyDoNotNeedToClickToEarnRewards) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(kRemindersFeature);

  RemindUserTheyDoNotNeedToClickToEarnRewards();

  // Act & Assert
  EXPECT_CALL(*ads_observer_mock_,
              OnRemindUser(mojom::ReminderType::kClickedSameAdMultipleTimes));
  RemindUserTheyDoNotNeedToClickToEarnRewards();
}

}  // namespace qorai_ads
