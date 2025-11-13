/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/history/ad_history_manager.h"

#include "qorai/components/qorai_ads/core/internal/ad_units/promoted_content_ad/promoted_content_ad_info.h"
#include "qorai/components/qorai_ads/core/internal/ad_units/search_result_ad/search_result_ad_builder.h"
#include "qorai/components/qorai_ads/core/internal/ad_units/search_result_ad/search_result_ad_info.h"
#include "qorai/components/qorai_ads/core/internal/ad_units/search_result_ad/search_result_ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/creatives/inline_content_ads/creative_inline_content_ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/inline_content_ads/inline_content_ad_builder.h"
#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/new_tab_page_ad_builder.h"
#include "qorai/components/qorai_ads/core/internal/creatives/notification_ads/creative_notification_ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/notification_ads/notification_ad_builder.h"
#include "qorai/components/qorai_ads/core/internal/creatives/promoted_content_ads/creative_promoted_content_ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/promoted_content_ads/promoted_content_ad_builder.h"
#include "qorai/components/qorai_ads/core/internal/history/ad_history_builder_util.h"
#include "qorai/components/qorai_ads/core/internal/history/ad_history_manager_observer_mock.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_ads/core/public/ad_units/inline_content_ad/inline_content_ad_info.h"
#include "qorai/components/qorai_ads/core/public/ad_units/new_tab_page_ad/new_tab_page_ad_info.h"
#include "qorai/components/qorai_ads/core/public/ad_units/notification_ad/notification_ad_info.h"
#include "qorai/components/qorai_ads/core/public/history/ad_history_item_info.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsAdHistoryManagerTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    AdHistoryManager::GetInstance().AddObserver(
        &history_manager_observer_mock_);
  }

  void TearDown() override {
    AdHistoryManager::GetInstance().RemoveObserver(
        &history_manager_observer_mock_);

    test::TestBase::TearDown();
  }

  AdHistoryManagerObserverMock history_manager_observer_mock_;
};

TEST_F(QoraiAdsAdHistoryManagerTest, AddNotificationAdHistory) {
  // Arrange
  const CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*should_generate_random_uuids=*/true);
  const NotificationAdInfo ad = BuildNotificationAd(creative_ad);

  // Act & Assert
  const AdHistoryItemInfo expected_ad_history_item = BuildAdHistoryItem(
      ad, mojom::ConfirmationType::kViewedImpression, ad.title, ad.body);
  EXPECT_CALL(history_manager_observer_mock_,
              OnDidAddAdHistoryItem(expected_ad_history_item));
  AdHistoryManager::GetInstance().Add(
      ad, mojom::ConfirmationType::kViewedImpression);
}

TEST_F(QoraiAdsAdHistoryManagerTest,
       DoNotAddNotificationAdHistoryForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  const CreativeNotificationAdInfo creative_ad =
      test::BuildCreativeNotificationAd(/*should_generate_random_uuids=*/true);
  const NotificationAdInfo ad = BuildNotificationAd(creative_ad);

  // Act & Assert
  EXPECT_CALL(history_manager_observer_mock_, OnDidAddAdHistoryItem).Times(0);
  AdHistoryManager::GetInstance().Add(
      ad, mojom::ConfirmationType::kViewedImpression);
}

TEST_F(QoraiAdsAdHistoryManagerTest, AddNewTabPageAdHistory) {
  // Arrange
  const CreativeNewTabPageAdInfo creative_ad =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*should_generate_random_uuids=*/true);
  const NewTabPageAdInfo ad = BuildNewTabPageAd(creative_ad);

  // Act & Assert
  const AdHistoryItemInfo expected_ad_history_item = BuildAdHistoryItem(
      ad, mojom::ConfirmationType::kViewedImpression, ad.company_name, ad.alt);
  EXPECT_CALL(history_manager_observer_mock_,
              OnDidAddAdHistoryItem(expected_ad_history_item));
  AdHistoryManager::GetInstance().Add(
      ad, mojom::ConfirmationType::kViewedImpression);
}

TEST_F(QoraiAdsAdHistoryManagerTest,
       DoNotAddNewTabPageAdHistoryForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  const CreativeNewTabPageAdInfo creative_ad =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*should_generate_random_uuids=*/true);
  const NewTabPageAdInfo ad = BuildNewTabPageAd(creative_ad);

  // Act & Assert
  EXPECT_CALL(history_manager_observer_mock_, OnDidAddAdHistoryItem).Times(0);
  AdHistoryManager::GetInstance().Add(
      ad, mojom::ConfirmationType::kViewedImpression);
}

TEST_F(QoraiAdsAdHistoryManagerTest, AddPromotedContentAdHistory) {
  // Arrange
  const CreativePromotedContentAdInfo creative_ad =
      test::BuildCreativePromotedContentAd(
          /*should_generate_random_uuids=*/true);
  const PromotedContentAdInfo ad = BuildPromotedContentAd(creative_ad);

  // Act & Assert
  const AdHistoryItemInfo expected_ad_history_item = BuildAdHistoryItem(
      ad, mojom::ConfirmationType::kViewedImpression, ad.title, ad.description);
  EXPECT_CALL(history_manager_observer_mock_,
              OnDidAddAdHistoryItem(expected_ad_history_item));
  AdHistoryManager::GetInstance().Add(
      ad, mojom::ConfirmationType::kViewedImpression);
}

TEST_F(QoraiAdsAdHistoryManagerTest,
       DoNotAddPromotedContentAdHistoryForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  const CreativePromotedContentAdInfo creative_ad =
      test::BuildCreativePromotedContentAd(
          /*should_generate_random_uuids=*/true);

  const PromotedContentAdInfo ad = BuildPromotedContentAd(creative_ad);

  // Act & Assert
  EXPECT_CALL(history_manager_observer_mock_, OnDidAddAdHistoryItem).Times(0);
  AdHistoryManager::GetInstance().Add(
      ad, mojom::ConfirmationType::kViewedImpression);
}

TEST_F(QoraiAdsAdHistoryManagerTest, AddInlineContentAdHistory) {
  // Arrange
  const CreativeInlineContentAdInfo creative_ad =
      test::BuildCreativeInlineContentAd(/*should_generate_random_uuids=*/true);
  const InlineContentAdInfo ad = BuildInlineContentAd(creative_ad);

  // Act & Assert
  const AdHistoryItemInfo expected_ad_history_item = BuildAdHistoryItem(
      ad, mojom::ConfirmationType::kViewedImpression, ad.title, ad.description);
  EXPECT_CALL(history_manager_observer_mock_,
              OnDidAddAdHistoryItem(expected_ad_history_item));
  AdHistoryManager::GetInstance().Add(
      ad, mojom::ConfirmationType::kViewedImpression);
}

TEST_F(QoraiAdsAdHistoryManagerTest,
       DoNotAddInlineContentAdHistoryForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  const CreativeInlineContentAdInfo creative_ad =
      test::BuildCreativeInlineContentAd(/*should_generate_random_uuids=*/true);
  const InlineContentAdInfo ad = BuildInlineContentAd(creative_ad);

  // Act & Assert
  EXPECT_CALL(history_manager_observer_mock_, OnDidAddAdHistoryItem).Times(0);
  AdHistoryManager::GetInstance().Add(
      ad, mojom::ConfirmationType::kViewedImpression);
}

TEST_F(QoraiAdsAdHistoryManagerTest, AddSearchResultAdHistory) {
  // Arrange
  const SearchResultAdInfo ad =
      test::BuildSearchResultAd(/*should_generate_random_uuids=*/true);

  // Act & Assert
  const AdHistoryItemInfo expected_ad_history_item =
      BuildAdHistoryItem(ad, mojom::ConfirmationType::kViewedImpression,
                         ad.headline_text, ad.description);
  EXPECT_CALL(history_manager_observer_mock_,
              OnDidAddAdHistoryItem(expected_ad_history_item));
  AdHistoryManager::GetInstance().Add(
      ad, mojom::ConfirmationType::kViewedImpression);
}

TEST_F(QoraiAdsAdHistoryManagerTest,
       DoNotAddSearchResultAdHistoryForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  const SearchResultAdInfo ad =
      test::BuildSearchResultAd(/*should_generate_random_uuids=*/true);

  // Act & Assert
  EXPECT_CALL(history_manager_observer_mock_, OnDidAddAdHistoryItem).Times(0);
  AdHistoryManager::GetInstance().Add(
      ad, mojom::ConfirmationType::kViewedImpression);
}

}  // namespace qorai_ads
