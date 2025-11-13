/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_attention/user_activity/page_transition_util.h"

#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsPageTransitionUtilTest, IsNewNavigation) {
  // Act & Assert
  EXPECT_TRUE(IsNewNavigation(kPageTransitionTyped));
}

TEST(QoraiAdsPageTransitionUtilTest,
     DidUseBackOrFowardButtonToTriggerNavigation) {
  // Act & Assert
  EXPECT_TRUE(
      DidUseBackOrFowardButtonToTriggerNavigation(kPageTransitionForwardBack));
}

TEST(QoraiAdsPageTransitionUtilTest, DidUseAddressBarToTriggerNavigation) {
  // Act & Assert
  EXPECT_TRUE(
      DidUseAddressBarToTriggerNavigation(kPageTransitionFromAddressBar));
}

TEST(QoraiAdsPageTransitionUtilTest, DidNavigateToHomePage) {
  // Act & Assert
  EXPECT_TRUE(DidNavigateToHomePage(kPageTransitionHomePage));
}

TEST(QoraiAdsPageTransitionUtilTest, DidTransitionFromExternalApplication) {
  // Act & Assert
  EXPECT_TRUE(DidTransitionFromExternalApplication(kPageTransitionFromAPI));
}

TEST(QoraiAdsPageTransitionUtilTest, ToUserActivityClickedLinkEventType) {
  // Act & Assert
  EXPECT_EQ(UserActivityEventType::kClickedLink,
            ToUserActivityEventType(kPageTransitionLink));
}

TEST(QoraiAdsPageTransitionUtilTest, ToUserActivityTypedUrlEventType) {
  // Act & Assert
  EXPECT_EQ(UserActivityEventType::kTypedUrl,
            ToUserActivityEventType(kPageTransitionTyped));
}

TEST(QoraiAdsPageTransitionUtilTest, ToUserActivityClickedBookmarkEventType) {
  // Act & Assert
  EXPECT_EQ(UserActivityEventType::kClickedBookmark,
            ToUserActivityEventType(kPageTransitionAutoBookmark));
}

TEST(QoraiAdsPageTransitionUtilTest,
     ToUserActivityTypedAndSelectedNonUrlEventType) {
  // Act & Assert
  EXPECT_EQ(UserActivityEventType::kTypedAndSelectedNonUrl,
            ToUserActivityEventType(kPageTransitionGenerated));
}

TEST(QoraiAdsPageTransitionUtilTest, ToUserActivitySubmittedFormEventType) {
  // Act & Assert
  EXPECT_EQ(UserActivityEventType::kSubmittedForm,
            ToUserActivityEventType(kPageTransitionFormSubmit));
}

TEST(QoraiAdsPageTransitionUtilTest,
     ToUserActivityClickedReloadButtonEventType) {
  // Act & Assert
  EXPECT_EQ(UserActivityEventType::kClickedReloadButton,
            ToUserActivityEventType(kPageTransitionReload));
}

TEST(QoraiAdsPageTransitionUtilTest,
     ToUserActivityTypedKeywordOtherThanDefaultSearchProviderEventType) {
  // Act & Assert
  EXPECT_EQ(UserActivityEventType::kTypedKeywordOtherThanDefaultSearchProvider,
            ToUserActivityEventType(kPageTransitionKeyword));
}

TEST(QoraiAdsPageTransitionUtilTest, ToUserActivityGeneratedKeywordEventType) {
  // Act & Assert
  EXPECT_EQ(UserActivityEventType::kGeneratedKeyword,
            ToUserActivityEventType(kPageTransitionKeywordGenerated));
}

}  // namespace qorai_ads
