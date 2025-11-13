/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/notification_ads/notification_ad_event_handler.h"

#include "base/run_loop.h"
#include "base/test/gmock_callback_support.h"
#include "base/test/mock_callback.h"
#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/ad_units/notification_ad/notification_ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/creatives/notification_ads/notification_ad_builder.h"
#include "qorai/components/qorai_ads/core/internal/creatives/notification_ads/notification_ad_manager.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/notification_ads/notification_ad_event_handler_delegate_mock.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_ads/core/public/ad_units/notification_ad/notification_ad_info.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsNotificationAdEventHandlerTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    event_handler_.SetDelegate(&delegate_mock_);
  }

  void FireEventAndVerifyExpectations(
      const std::string& placement_id,
      mojom::NotificationAdEventType mojom_ad_event_type,
      bool should_fire_event) {
    base::MockCallback<FireNotificationAdEventHandlerCallback> callback;
    base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);
    EXPECT_CALL(callback, Run(/*success=*/should_fire_event, placement_id,
                              mojom_ad_event_type))
        .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
    event_handler_.FireEvent(placement_id, mojom_ad_event_type, callback.Get());
    run_loop.Run();
  }

  NotificationAdEventHandler event_handler_;
  ::testing::StrictMock<NotificationAdEventHandlerDelegateMock> delegate_mock_;
};

TEST_F(QoraiAdsNotificationAdEventHandlerTest, FireServedEvent) {
  // Arrange
  const NotificationAdInfo ad =
      test::BuildAndSaveNotificationAd(/*should_generate_random_uuids=*/false);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_, OnDidFireNotificationAdServedEvent(ad))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(
      ad.placement_id, mojom::NotificationAdEventType::kServedImpression,
      /*should_fire_event=*/true);
  run_loop.Run();
}

TEST_F(QoraiAdsNotificationAdEventHandlerTest, FireViewedEvent) {
  // Arrange
  const NotificationAdInfo ad =
      test::BuildAndSaveNotificationAd(/*should_generate_random_uuids=*/false);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_, OnDidFireNotificationAdViewedEvent(ad))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(
      ad.placement_id, mojom::NotificationAdEventType::kViewedImpression,
      /*should_fire_event=*/true);
  run_loop.Run();
}

TEST_F(QoraiAdsNotificationAdEventHandlerTest, FireClickedEvent) {
  // Arrange
  const NotificationAdInfo ad =
      test::BuildAndSaveNotificationAd(/*should_generate_random_uuids=*/false);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_, OnDidFireNotificationAdClickedEvent(ad))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(ad.placement_id,
                                 mojom::NotificationAdEventType::kClicked,
                                 /*should_fire_event=*/true);
  run_loop.Run();
}

TEST_F(QoraiAdsNotificationAdEventHandlerTest, FireDismissedEvent) {
  // Arrange
  const NotificationAdInfo ad =
      test::BuildAndSaveNotificationAd(/*should_generate_random_uuids=*/false);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_, OnDidFireNotificationAdDismissedEvent(ad))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(ad.placement_id,
                                 mojom::NotificationAdEventType::kDismissed,
                                 /*should_fire_event=*/true);
  run_loop.Run();
}

TEST_F(QoraiAdsNotificationAdEventHandlerTest, FireTimedOutEvent) {
  // Arrange
  const NotificationAdInfo ad =
      test::BuildAndSaveNotificationAd(/*should_generate_random_uuids=*/false);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_, OnDidFireNotificationAdTimedOutEvent(ad))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(ad.placement_id,
                                 mojom::NotificationAdEventType::kTimedOut,
                                 /*should_fire_event=*/true);
  run_loop.Run();
}

TEST_F(QoraiAdsNotificationAdEventHandlerTest,
       DoNotFireEventIfMissingPlacementId) {
  // Arrange
  const NotificationAdInfo ad =
      test::BuildAndSaveNotificationAd(/*should_generate_random_uuids=*/false);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_,
              OnFailedToFireNotificationAdEvent(
                  test::kMissingPlacementId,
                  mojom::NotificationAdEventType::kViewedImpression))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(
      test::kMissingPlacementId,
      mojom::NotificationAdEventType::kViewedImpression,
      /*should_fire_event=*/false);
  run_loop.Run();
}

}  // namespace qorai_ads
