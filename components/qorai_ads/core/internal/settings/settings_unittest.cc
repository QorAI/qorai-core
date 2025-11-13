/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/settings/settings.h"

#include "base/test/scoped_feature_list.h"
#include "qorai/components/qorai_ads/core/internal/common/test/profile_pref_value_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/public/ad_units/notification_ad/notification_ad_feature.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsSettingsTest : public test::TestBase {};

TEST_F(QoraiAdsSettingsTest, UserHasJoinedQoraiRewards) {
  // Act & Assert
  EXPECT_TRUE(UserHasJoinedQoraiRewards());
}

TEST_F(QoraiAdsSettingsTest, UserHasNotJoinedQoraiRewards) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  EXPECT_FALSE(UserHasJoinedQoraiRewards());
}

TEST_F(QoraiAdsSettingsTest, UserHasJoinedQoraiRewardsAndConnectedWallet) {
  // Act & Assert
  EXPECT_TRUE(UserHasJoinedQoraiRewardsAndConnectedWallet());
  EXPECT_FALSE(UserHasJoinedQoraiRewardsAndNotConnectedWallet());
}

TEST_F(QoraiAdsSettingsTest, UserHasJoinedQoraiRewardsAndNotConnectedWallet) {
  // Arrange
  test::DisconnectExternalQoraiRewardsWallet();

  // Act & Assert
  EXPECT_FALSE(UserHasJoinedQoraiRewardsAndConnectedWallet());
  EXPECT_TRUE(UserHasJoinedQoraiRewardsAndNotConnectedWallet());
}

TEST_F(QoraiAdsSettingsTest, UserHasOptedInToQoraiNewsAds) {
  // Act & Assert
  EXPECT_TRUE(UserHasOptedInToQoraiNewsAds());
}

TEST_F(QoraiAdsSettingsTest, UserHasNotOptedInToQoraiNews) {
  // Arrange
  test::OptOutOfQoraiNewsAds();

  // Act & Assert
  EXPECT_FALSE(UserHasOptedInToQoraiNewsAds());
}

TEST_F(QoraiAdsSettingsTest, UserHasOptedInToNewTabPageAds) {
  // Act & Assert
  EXPECT_TRUE(UserHasOptedInToNewTabPageAds());
}

TEST_F(QoraiAdsSettingsTest, UserHasNotOptedInToNewTabPageAds) {
  // Arrange
  test::OptOutOfNewTabPageAds();

  // Act & Assert
  EXPECT_FALSE(UserHasOptedInToNewTabPageAds());
}

TEST_F(QoraiAdsSettingsTest, UserHasOptedInToNotificationAds) {
  // Act & Assert
  EXPECT_TRUE(UserHasOptedInToNotificationAds());
}

TEST_F(QoraiAdsSettingsTest, UserHasNotOptedInToNotificationAds) {
  // Arrange
  test::OptOutOfNotificationAds();

  // Act & Assert
  EXPECT_FALSE(UserHasOptedInToNotificationAds());
}

TEST_F(QoraiAdsSettingsTest, MaximumNotificationAdsPerHour) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kNotificationAdFeature, {{"default_ads_per_hour", "2"}});

  test::SetProfileInt64PrefValue(prefs::kMaximumNotificationAdsPerHour, 3);

  // Act & Assert
  EXPECT_EQ(3, GetMaximumNotificationAdsPerHour());
}

TEST_F(QoraiAdsSettingsTest, DefaultMaximumNotificationAdsPerHour) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kNotificationAdFeature, {{"default_ads_per_hour", "2"}});

  // Act & Assert
  EXPECT_EQ(2, GetMaximumNotificationAdsPerHour());
}

TEST_F(QoraiAdsSettingsTest, UserHasOptedInToSearchResultAds) {
  // Act & Assert
  EXPECT_TRUE(UserHasOptedInToSearchResultAds());
}

TEST_F(QoraiAdsSettingsTest, UserHasNotOptedInToSearchResultAds) {
  // Arrange
  test::OptOutOfSearchResultAds();

  // Act & Assert
  EXPECT_FALSE(UserHasOptedInToSearchResultAds());
}

}  // namespace qorai_ads
