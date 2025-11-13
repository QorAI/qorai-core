/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/media_permission_rule.h"

#include "base/test/scoped_feature_list.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/permission_rule_feature.h"
#include "net/http/http_status_code.h"
#include "url/gurl.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsMediaPermissionRuleTest : public test::TestBase {};

TEST_F(QoraiAdsMediaPermissionRuleTest, ShouldAllowIfMediaIsNotPlaying) {
  // Act & Assert
  EXPECT_TRUE(HasMediaPermission());
}

TEST_F(QoraiAdsMediaPermissionRuleTest,
       ShouldAllowIfMediaIsStoppedForSingleTab) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);

  NotifyTabDidStartPlayingMedia(/*tab_id=*/1);

  NotifyTabDidStopPlayingMedia(/*tab_id=*/1);

  // Act & Assert
  EXPECT_TRUE(HasMediaPermission());
}

TEST_F(QoraiAdsMediaPermissionRuleTest,
       ShouldAllowIfMediaIsStoppedOnMultipleTabs) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);

  NotifyTabDidStartPlayingMedia(/*tab_id=*/1);
  NotifyTabDidStartPlayingMedia(/*tab_id=*/2);

  NotifyTabDidStopPlayingMedia(/*tab_id=*/1);
  NotifyTabDidStopPlayingMedia(/*tab_id=*/2);

  // Act & Assert
  EXPECT_TRUE(HasMediaPermission());
}

TEST_F(QoraiAdsMediaPermissionRuleTest,
       ShouldAllowIfMediaIsPlayingOnMultipleTabsButStoppedForVisibleTab) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);

  NotifyTabDidStartPlayingMedia(/*tab_id=*/1);
  NotifyTabDidStartPlayingMedia(/*tab_id=*/2);

  NotifyTabDidStopPlayingMedia(/*tab_id=*/1);

  // Act & Assert
  EXPECT_TRUE(HasMediaPermission());
}

TEST_F(QoraiAdsMediaPermissionRuleTest,
       ShouldNotAllowIfMediaIsPlayingOnVisibleTab) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);

  NotifyTabDidStartPlayingMedia(/*tab_id=*/1);

  // Act & Assert
  EXPECT_FALSE(HasMediaPermission());
}

TEST_F(
    QoraiAdsMediaPermissionRuleTest,
    ShouldAlwaysAllowIfMediaIsPlayingOnVisibleTabIfPermissionRuleIsDisabled) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kPermissionRulesFeature,
      {{"should_only_serve_ads_if_media_is_not_playing", "false"}});

  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);

  NotifyTabDidStartPlayingMedia(/*tab_id=*/1);

  // Act & Assert
  EXPECT_TRUE(HasMediaPermission());
}

TEST_F(QoraiAdsMediaPermissionRuleTest,
       ShouldNotAllowIfMediaIsPlayingOnMultipleTabs) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);

  NotifyTabDidStartPlayingMedia(/*tab_id=*/1);
  NotifyTabDidStartPlayingMedia(/*tab_id=*/2);

  // Act & Assert
  EXPECT_FALSE(HasMediaPermission());
}

TEST_F(QoraiAdsMediaPermissionRuleTest,
       ShouldNotAllowIfMediaIsPlayingOnMultipleTabsButStoppedForOccludedTab) {
  // Arrange
  const base::test::ScopedFeatureList scoped_feature_list(
      kPermissionRulesFeature);

  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);

  NotifyTabDidStartPlayingMedia(/*tab_id=*/1);
  NotifyTabDidStartPlayingMedia(/*tab_id=*/2);

  NotifyTabDidStopPlayingMedia(/*tab_id=*/2);

  // Act & Assert
  EXPECT_FALSE(HasMediaPermission());
}

}  // namespace qorai_ads
