/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "base/run_loop.h"
#include "base/test/gmock_callback_support.h"
#include "base/test/mock_callback.h"
#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/ad_units/new_tab_page_ad/new_tab_page_ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type.h"
#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/new_tab_page_ad_builder.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_test_util.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/new_tab_page_ads/new_tab_page_ad_event_handler.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/new_tab_page_ads/new_tab_page_ad_event_handler_delegate_mock.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_info.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsNewTabPageAdEventHandlerIfUserHasNotJoinedQoraiRewardsTest
    : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    test::DisableQoraiRewards();

    event_handler_.SetDelegate(&delegate_mock_);
  }

  void FireEventAndVerifyExpectations(
      const std::string& placement_id,
      const std::string& creative_instance_id,
      mojom::NewTabPageAdEventType mojom_ad_event_type,
      bool should_fire_event) {
    base::MockCallback<FireNewTabPageAdEventHandlerCallback> callback;
    base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);
    EXPECT_CALL(callback, Run(/*success=*/should_fire_event, placement_id,
                              mojom_ad_event_type))
        .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
    event_handler_.FireEvent(placement_id, creative_instance_id,
                             mojom_ad_event_type, callback.Get());
    run_loop.Run();
  }

  NewTabPageAdEventHandler event_handler_;
  ::testing::StrictMock<NewTabPageAdEventHandlerDelegateMock> delegate_mock_;
};

TEST_F(QoraiAdsNewTabPageAdEventHandlerIfUserHasNotJoinedQoraiRewardsTest,
       FireServedEvent) {
  // Arrange
  const NewTabPageAdInfo ad =
      test::BuildAndSaveNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                     /*should_generate_random_uuids=*/false);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_, OnDidFireNewTabPageAdServedEvent(ad))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(
      ad.placement_id, ad.creative_instance_id,
      mojom::NewTabPageAdEventType::kServedImpression,
      /*should_fire_event=*/true);
  run_loop.Run();
}

TEST_F(QoraiAdsNewTabPageAdEventHandlerIfUserHasNotJoinedQoraiRewardsTest,
       FireViewedEvent) {
  // Arrange
  const NewTabPageAdInfo ad =
      test::BuildAndSaveNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                     /*should_generate_random_uuids=*/false);
  test::RecordAdEvent(ad, mojom::ConfirmationType::kServedImpression);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_, OnDidFireNewTabPageAdViewedEvent(ad))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(
      ad.placement_id, ad.creative_instance_id,
      mojom::NewTabPageAdEventType::kViewedImpression,
      /*should_fire_event=*/true);
  run_loop.Run();
}

TEST_F(QoraiAdsNewTabPageAdEventHandlerIfUserHasNotJoinedQoraiRewardsTest,
       DoNotFireViewedEventIfAdPlacementWasAlreadyViewed) {
  // Arrange
  const NewTabPageAdInfo ad =
      test::BuildAndSaveNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                     /*should_generate_random_uuids=*/false);
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression});

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_,
              OnFailedToFireNewTabPageAdEvent(
                  ad.placement_id, ad.creative_instance_id,
                  mojom::NewTabPageAdEventType::kViewedImpression))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(
      ad.placement_id, ad.creative_instance_id,
      mojom::NewTabPageAdEventType::kViewedImpression,
      /*should_fire_event=*/false);
  run_loop.Run();
}

TEST_F(QoraiAdsNewTabPageAdEventHandlerIfUserHasNotJoinedQoraiRewardsTest,
       DoNotFireViewedEventIfAdPlacementWasNotServed) {
  // Arrange
  const NewTabPageAdInfo ad =
      test::BuildAndSaveNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                     /*should_generate_random_uuids=*/false);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_,
              OnFailedToFireNewTabPageAdEvent(
                  ad.placement_id, ad.creative_instance_id,
                  mojom::NewTabPageAdEventType::kViewedImpression))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(
      ad.placement_id, ad.creative_instance_id,
      mojom::NewTabPageAdEventType::kViewedImpression,
      /*should_fire_event=*/false);
  run_loop.Run();
}

TEST_F(QoraiAdsNewTabPageAdEventHandlerIfUserHasNotJoinedQoraiRewardsTest,
       FireClickedEvent) {
  // Arrange
  const NewTabPageAdInfo ad =
      test::BuildAndSaveNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                     /*should_generate_random_uuids=*/false);
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression});

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_, OnDidFireNewTabPageAdClickedEvent(ad))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(ad.placement_id, ad.creative_instance_id,
                                 mojom::NewTabPageAdEventType::kClicked,
                                 /*should_fire_event=*/true);
  run_loop.Run();
}

TEST_F(QoraiAdsNewTabPageAdEventHandlerIfUserHasNotJoinedQoraiRewardsTest,
       DoNotFireClickedEventIfAdPlacementWasAlreadyClicked) {
  // Arrange
  const NewTabPageAdInfo ad =
      test::BuildAndSaveNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                     /*should_generate_random_uuids=*/false);
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression,
                            mojom::ConfirmationType::kClicked});

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_, OnFailedToFireNewTabPageAdEvent(
                                  ad.placement_id, ad.creative_instance_id,
                                  mojom::NewTabPageAdEventType::kClicked))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(ad.placement_id, ad.creative_instance_id,
                                 mojom::NewTabPageAdEventType::kClicked,
                                 /*should_fire_event=*/false);
  run_loop.Run();
}

TEST_F(QoraiAdsNewTabPageAdEventHandlerIfUserHasNotJoinedQoraiRewardsTest,
       DoNotFireClickedEventIfAdPlacementWasNotServed) {
  // Arrange
  const NewTabPageAdInfo ad =
      test::BuildAndSaveNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                     /*should_generate_random_uuids=*/false);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_, OnFailedToFireNewTabPageAdEvent(
                                  ad.placement_id, ad.creative_instance_id,
                                  mojom::NewTabPageAdEventType::kClicked))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(ad.placement_id, ad.creative_instance_id,
                                 mojom::NewTabPageAdEventType::kClicked,
                                 /*should_fire_event=*/false);
  run_loop.Run();
}

TEST_F(QoraiAdsNewTabPageAdEventHandlerIfUserHasNotJoinedQoraiRewardsTest,
       DoNotFireEventWithInvalidPlacementId) {
  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_,
              OnFailedToFireNewTabPageAdEvent(
                  test::kInvalidPlacementId, test::kCreativeInstanceId,
                  mojom::NewTabPageAdEventType::kServedImpression))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(
      test::kInvalidPlacementId, test::kCreativeInstanceId,
      mojom::NewTabPageAdEventType::kServedImpression,
      /*should_fire_event=*/false);
  run_loop.Run();
}

TEST_F(QoraiAdsNewTabPageAdEventHandlerIfUserHasNotJoinedQoraiRewardsTest,
       DoNotFireEventWithInvalidCreativeInstanceId) {
  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_,
              OnFailedToFireNewTabPageAdEvent(
                  test::kPlacementId, test::kInvalidCreativeInstanceId,
                  mojom::NewTabPageAdEventType::kServedImpression))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(
      test::kPlacementId, test::kInvalidCreativeInstanceId,
      mojom::NewTabPageAdEventType::kServedImpression,
      /*should_fire_event=*/false);
  run_loop.Run();
}

TEST_F(QoraiAdsNewTabPageAdEventHandlerIfUserHasNotJoinedQoraiRewardsTest,
       DoNotFireEventForMissingCreativeInstanceId) {
  // Arrange
  const NewTabPageAdInfo ad =
      test::BuildAndSaveNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                     /*should_generate_random_uuids=*/false);

  // Act & Assert
  base::RunLoop run_loop;
  EXPECT_CALL(delegate_mock_,
              OnFailedToFireNewTabPageAdEvent(
                  ad.placement_id, test::kMissingCreativeInstanceId,
                  mojom::NewTabPageAdEventType::kServedImpression))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  FireEventAndVerifyExpectations(
      ad.placement_id, test::kMissingCreativeInstanceId,
      mojom::NewTabPageAdEventType::kServedImpression,
      /*should_fire_event=*/false);
  run_loop.Run();
}

}  // namespace qorai_ads
