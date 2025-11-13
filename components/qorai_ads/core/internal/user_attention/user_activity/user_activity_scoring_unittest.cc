/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_scoring.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_manager.h"
#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_trigger_info.h"
#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/user_activity_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsUserActivityScoringTest : public test::TestBase {};

TEST_F(QoraiAdsUserActivityScoringTest, GetUserActivityScore) {
  // Arrange
  const UserActivityTriggerList triggers =
      ToUserActivityTriggers("06=.3;0D1406=1.0;0D14=0.5");

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedReloadButton);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Hours(1));

  // Act & Assert
  EXPECT_EQ(1.8, GetUserActivityScore(triggers, events));
}

TEST_F(QoraiAdsUserActivityScoringTest, GetUserActivityScoreForTimeWindow) {
  // Arrange
  const UserActivityTriggerList triggers =
      ToUserActivityTriggers("06=.3;0D1406=1.0;0D14=0.5");

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  AdvanceClockBy(base::Hours(2));
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedReloadButton);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Hours(1));

  // Act & Assert
  EXPECT_EQ(1.5, GetUserActivityScore(triggers, events));
}

TEST_F(QoraiAdsUserActivityScoringTest,
       GetUserActivityScoreForInvalidEventSequence) {
  // Arrange
  const UserActivityTriggerList triggers = ToUserActivityTriggers("INVALID");

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedReloadButton);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Hours(1));

  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, GetUserActivityScore(triggers, events));
}

TEST_F(QoraiAdsUserActivityScoringTest,
       GetUserActivityScoreForMalformedEventSequence) {
  // Arrange
  const UserActivityTriggerList triggers =
      ToUserActivityTriggers("06=1;0D1406=1.0;=0.5");

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedReloadButton);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Hours(1));

  // Act & Assert
  EXPECT_EQ(2.0, GetUserActivityScore(triggers, events));
}

TEST_F(QoraiAdsUserActivityScoringTest,
       GetUserActivityScoreForMixedCaseEventSequence) {
  // Arrange
  const UserActivityTriggerList triggers =
      ToUserActivityTriggers("06=.3;0d1406=1.0;0D14=0.5");

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedReloadButton);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Hours(1));

  // Act & Assert
  EXPECT_EQ(1.8, GetUserActivityScore(triggers, events));
}

TEST_F(QoraiAdsUserActivityScoringTest,
       GetUserActivityScoreForEmptyEventSequence) {
  // Arrange
  const UserActivityTriggerList triggers =
      ToUserActivityTriggers(/*param_value=*/{});

  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedReloadButton);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTabStartedPlayingMedia);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kOpenedNewTab);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kTypedUrl);
  UserActivityManager::GetInstance().RecordEvent(
      UserActivityEventType::kClickedLink);

  const UserActivityEventList events =
      UserActivityManager::GetInstance().GetHistoryForTimeWindow(
          base::Hours(1));

  // Act & Assert
  EXPECT_DOUBLE_EQ(0.0, GetUserActivityScore(triggers, events));
}

}  // namespace qorai_ads
