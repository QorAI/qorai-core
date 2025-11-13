/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/eligible_ads/exclusion_rules/anti_targeting_exclusion_rule_util.h"

#include "qorai/components/qorai_ads/core/internal/history/site_history_test_util.h"
#include "qorai/components/qorai_ads/core/public/history/site_history.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsAntiTargetingExclusionRuleUtilTest, HasVisitedAntiTargetedSites) {
  // Arrange
  const SiteHistoryList site_history = test::BuildSiteHistory();

  const AntiTargetingSiteList anti_targeting_sites = {
      GURL("https://www.foo.com"), GURL("https://www.bar.com")};

  // Act & Assert
  EXPECT_TRUE(HasVisitedAntiTargetedSites(site_history, anti_targeting_sites));
}

TEST(QoraiAdsAntiTargetingExclusionRuleUtilTest,
     HasVisitedCaseInsensitiveAntiTargetedSites) {
  // Arrange
  const SiteHistoryList site_history = test::BuildSiteHistory();

  const AntiTargetingSiteList anti_targeting_sites = {
      GURL("HTTPS://WWW.FOO.COM"), GURL("HTTPS://WWW.BAR.COM")};

  // Act & Assert
  EXPECT_TRUE(HasVisitedAntiTargetedSites(site_history, anti_targeting_sites));
}

TEST(QoraiAdsAntiTargetingExclusionRuleUtilTest,
     HasNotVisitedAntiTargetedSites) {
  // Arrange
  const SiteHistoryList site_history = test::BuildSiteHistory();

  const AntiTargetingSiteList anti_targeting_sites = {
      GURL("https://www.qorai.com"),
      GURL("https://www.basicattentiontoken.org")};

  // Act & Assert
  EXPECT_FALSE(HasVisitedAntiTargetedSites(site_history, anti_targeting_sites));
}

TEST(QoraiAdsAntiTargetingExclusionRuleUtilTest,
     HasNotVisitedAntiTargetedInvalidSites) {
  // Arrange
  const SiteHistoryList site_history = test::BuildSiteHistory();

  const AntiTargetingSiteList anti_targeting_sites = {GURL("INVALID")};

  // Act & Assert
  EXPECT_FALSE(HasVisitedAntiTargetedSites(site_history, anti_targeting_sites));
}

TEST(QoraiAdsAntiTargetingExclusionRuleUtilTest, HasNotVisitedIfNoSiteHistory) {
  // Arrange
  const AntiTargetingSiteList anti_targeting_sites = {GURL("INVALID")};

  // Act & Assert
  EXPECT_FALSE(
      HasVisitedAntiTargetedSites(/*site_history=*/{}, anti_targeting_sites));
}

TEST(QoraiAdsAntiTargetingExclusionRuleUtilTest,
     HasNotVisitedIfNoAntiTargetedSites) {
  // Arrange
  const SiteHistoryList site_history = test::BuildSiteHistory();

  // Act & Assert
  EXPECT_FALSE(HasVisitedAntiTargetedSites(site_history, /*sites=*/{}));
}

TEST(QoraiAdsAntiTargetingExclusionRuleUtilTest,
     HasNotVisitedIfNoSiteHistoryAndAntiTargetedSites) {
  // Act & Assert
  EXPECT_FALSE(HasVisitedAntiTargetedSites(/*site_history=*/{}, /*sites=*/{}));
}

}  // namespace qorai_ads
