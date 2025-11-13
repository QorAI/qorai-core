/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/site_visit/site_visit_util.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "net/http/http_status_code.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsSiteVisitUtilTest : public test::TestBase {};

TEST_F(QoraiAdsSiteVisitUtilTest,
       AllowInlineContentAdPageLandIfRewardsUserAndOptedInToQoraiNews) {
  // Act & Assert
  EXPECT_TRUE(IsAllowedToLandOnPage(mojom::AdType::kInlineContentAd));
}

TEST_F(QoraiAdsSiteVisitUtilTest,
       DoNotAllowInlineContentAdPageLandIfRewardsUserAndOptedOutOfQoraiNews) {
  // Arrange
  test::OptOutOfQoraiNewsAds();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kInlineContentAd));
}

TEST_F(QoraiAdsSiteVisitUtilTest,
       AllowInlineContentAdPageLandIfNonRewardsUserAndOptedInToQoraiNews) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  EXPECT_TRUE(IsAllowedToLandOnPage(mojom::AdType::kInlineContentAd));
}

TEST_F(
    QoraiAdsSiteVisitUtilTest,
    DoNotAllowInlineContentAdPageLandIfNonRewardsUserAndOptedOutOfQoraiNews) {
  // Arrange
  test::DisableQoraiRewards();
  test::OptOutOfQoraiNewsAds();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kInlineContentAd));
}

TEST_F(QoraiAdsSiteVisitUtilTest,
       AllowPromotedContentAdPageLandIfRewardsUserAndOptedInToQoraiNews) {
  // Act & Assert
  EXPECT_TRUE(IsAllowedToLandOnPage(mojom::AdType::kPromotedContentAd));
}

TEST_F(QoraiAdsSiteVisitUtilTest,
       DoNotAllowPromotedContentAdPageLandIfRewardsUserAndOptedOutOfQoraiNews) {
  // Arrange
  test::OptOutOfQoraiNewsAds();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kPromotedContentAd));
}

TEST_F(QoraiAdsSiteVisitUtilTest,
       AllowPromotedContentAdPageLandIfNonRewardsUserAndOptedInToQoraiNews) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  EXPECT_TRUE(IsAllowedToLandOnPage(mojom::AdType::kPromotedContentAd));
}

TEST_F(
    QoraiAdsSiteVisitUtilTest,
    DoNotAllowPromotedContentAdPageLandIfNonRewardsUserAndOptedOutOfQoraiNews) {
  // Arrange
  test::DisableQoraiRewards();
  test::OptOutOfQoraiNewsAds();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kPromotedContentAd));
}

TEST_F(QoraiAdsSiteVisitUtilTest,
       AllowNewTabPageAdPageLandIfRewardsUserAndOptedInToNewTabPageAds) {
  // Act & Assert
  EXPECT_TRUE(IsAllowedToLandOnPage(mojom::AdType::kNewTabPageAd));
}

TEST_F(QoraiAdsSiteVisitUtilTest,
       DoNotAllowNewTabPageAdPageLandIfRewardsUserAndOptedOutOfNewTabPageAds) {
  // Arrange
  test::OptOutOfNewTabPageAds();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kNewTabPageAd));
}

TEST_F(
    QoraiAdsSiteVisitUtilTest,
    DoNotAllowNewTabPageAdPageLandIfNonRewardsUserAndOptedInToNewTabPageAds) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kNewTabPageAd));
}

TEST_F(
    QoraiAdsSiteVisitUtilTest,
    DoNotAllowNewTabPageAdPageLandIfNonRewardsUserAndOptedOutOfNewTabPageAds) {
  // Arrange
  test::DisableQoraiRewards();
  test::OptOutOfNewTabPageAds();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kNewTabPageAd));
}

TEST_F(QoraiAdsSiteVisitUtilTest,
       AllowNotificationAdPageLandIfRewardsUserAndOptedInToNotificationAds) {
  // Act & Assert
  EXPECT_TRUE(IsAllowedToLandOnPage(mojom::AdType::kNotificationAd));
}

TEST_F(
    QoraiAdsSiteVisitUtilTest,
    DoNotAllowNotificationAdPageLandIfRewardsUserAndOptedOutOfNotificationAds) {
  // Arrange
  test::OptOutOfNotificationAds();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kNotificationAd));
}

TEST_F(QoraiAdsSiteVisitUtilTest,
       DoNotAllowNotificationAdPageLandIfNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kNotificationAd));
}

TEST_F(QoraiAdsSiteVisitUtilTest,
       AllowSearchResultAdPageLandIfRewardsUserAndOptedInToSearchResultAds) {
  // Act & Assert
  EXPECT_TRUE(IsAllowedToLandOnPage(mojom::AdType::kSearchResultAd));
}

TEST_F(
    QoraiAdsSiteVisitUtilTest,
    DoNotAllowSearchResultAdPageLandIfRewardsUserAndOptedOutOfSearchResultAds) {
  // Arrange
  test::OptOutOfSearchResultAds();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kSearchResultAd));
}

TEST_F(
    QoraiAdsSiteVisitUtilTest,
    DoNotAllowSearchResultAdPageLandIfNonRewardsUserAndOptedInToSearchResultAds) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  EXPECT_FALSE(IsAllowedToLandOnPage(mojom::AdType::kSearchResultAd));
}

TEST_F(QoraiAdsSiteVisitUtilTest, ShouldResumePageLand) {
  // Arrange
  NotifyBrowserDidBecomeActive();
  NotifyBrowserDidEnterForeground();

  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);

  // Act & Assert
  EXPECT_TRUE(ShouldResumePageLand(/*tab_id=*/1));
}

TEST_F(QoraiAdsSiteVisitUtilTest, ShouldNotResumePageLandIfTabIsOccluded) {
  // Arrange
  NotifyBrowserDidBecomeActive();
  NotifyBrowserDidEnterForeground();

  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);
  SimulateOpeningNewTab(
      /*tab_id=*/2,
      /*redirect_chain=*/{GURL("https://basicattentiontoken.org")},
      net::HTTP_OK);

  // Act & Assert
  EXPECT_FALSE(ShouldResumePageLand(/*tab_id=*/1));
}

TEST_F(QoraiAdsSiteVisitUtilTest, ShouldNotResumePageLandIfBrowserIsInactive) {
  // Arrange
  NotifyBrowserDidResignActive();
  NotifyBrowserDidEnterForeground();

  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);

  // Act & Assert
  EXPECT_FALSE(ShouldResumePageLand(/*tab_id=*/1));
}

TEST_F(QoraiAdsSiteVisitUtilTest,
       ShouldNotResumePageLandIfBrowserDidEnterBackground) {
  // Arrange
  NotifyBrowserDidBecomeActive();
  NotifyBrowserDidEnterBackground();

  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);

  // Act & Assert
  EXPECT_FALSE(ShouldResumePageLand(/*tab_id=*/1));
}

TEST_F(QoraiAdsSiteVisitUtilTest, DidLandOnPage) {
  // Arrange
  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);

  // Act & Assert
  EXPECT_TRUE(DidLandOnPage(/*tab_id=*/1, GURL("https://qorai.com")));
}

TEST_F(QoraiAdsSiteVisitUtilTest, DoNotLandOnPageForClosedTab) {
  // Arrange
  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);

  NotifyDidCloseTab(/*tab_id=*/1);

  // Act & Assert
  EXPECT_FALSE(DidLandOnPage(/*tab_id=*/1, GURL("https://qorai.com")));
}

TEST_F(QoraiAdsSiteVisitUtilTest, DoNotLandOnPageForDomainOrHostMismatch) {
  // Arrange
  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://foo.com")},
                        net::HTTP_OK);

  // Act & Assert
  EXPECT_FALSE(DidLandOnPage(/*tab_id=*/1, GURL("https://qorai.com")));
}

}  // namespace qorai_ads
