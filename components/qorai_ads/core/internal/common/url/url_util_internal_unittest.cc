/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/url/url_util_internal.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads::internal {

TEST(QoraiAdsUrlUtilInternalTest, HasUrlSearchQueryNameAndValue) {
  // Act & Assert
  EXPECT_TRUE(HasSearchQuery(GURL("https://xyzzy.com/?search=thud")));
}

TEST(QoraiAdsUrlUtilInternalTest, DoesNotHaveUrlSearchQueryName) {
  // Act & Assert
  EXPECT_FALSE(HasSearchQuery(GURL("https://xyzzy.com/?foo=bar")));
}

TEST(QoraiAdsUrlUtilInternalTest, HasUrlSearchQueryNameAndEmptyValue) {
  // Act & Assert
  EXPECT_FALSE(HasSearchQuery(GURL("https://xyzzy.com/?search=")));
}

TEST(QoraiAdsUrlUtilInternalTest, HasSearchQueryNameWithNoValue) {
  // Act & Assert
  EXPECT_FALSE(HasSearchQuery(GURL("https://xyzzy.com/?search")));
}

TEST(QoraiAdsUrlUtilInternalTest, DoesETLDPlusOneContainWildcards) {
  // Act & Assert
  EXPECT_TRUE(DoesETLDPlusOneContainWildcards(GURL("https://*.appspot.com")));
  EXPECT_TRUE(DoesETLDPlusOneContainWildcards(GURL("https://*.com")));
}

TEST(QoraiAdsUrlUtilInternalTest, DoesETLDPlusOneNotContainWildcards) {
  // Act & Assert
  EXPECT_FALSE(DoesETLDPlusOneContainWildcards(GURL("https://*.xyzzy.com")));
  EXPECT_FALSE(
      DoesETLDPlusOneContainWildcards(GURL("https://*.r.appspot.com")));
}

TEST(QoraiAdsUrlUtilInternalTest, HostHasRegistryControlledDomain) {
  // Act & Assert
  EXPECT_TRUE(HostHasRegistryControlledDomain("mysite.appspot.com"));
  EXPECT_TRUE(HostHasRegistryControlledDomain("https://www.google.co.uk"));
  EXPECT_TRUE(HostHasRegistryControlledDomain("https://google.co.uk"));
  EXPECT_TRUE(HostHasRegistryControlledDomain("https://foo.aeroclub.aero"));
  EXPECT_TRUE(
      HostHasRegistryControlledDomain("https://example.mysite.appspot.com"));
}

TEST(QoraiAdsUrlUtilInternalTest, HostDoesNotHaveRegistryControlledDomain) {
  // Act & Assert
  EXPECT_FALSE(HostHasRegistryControlledDomain("https://hello.unknown"));
}

TEST(QoraiAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithQoraiSchemeAndFooBarHostName) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://foobar")));
}

TEST(QoraiAdsUrlUtilInternalTest,
     ShouldSupportInternalUrlWithQoraiSchemeAndGettingStartedHostName) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportInternalUrl(GURL("chrome://getting-started")));
}

TEST(
    QoraiAdsUrlUtilInternalTest,
    ShouldNotSupportInternalUrlWithQoraiSchemeAndGettingStartedHostNameAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://getting-started/foo")));
}

TEST(QoraiAdsUrlUtilInternalTest,
     ShouldSupportInternalUrlWithQoraiSchemeAndWalletHostName) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportInternalUrl(GURL("chrome://wallet")));
}

TEST(QoraiAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithQoraiSchemeAndWalletHostNameAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://wallet/foo")));
}

TEST(QoraiAdsUrlUtilInternalTest,
     ShouldSupportInternalUrlWithQoraiSchemeAndSyncHostName) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportInternalUrl(GURL("chrome://sync")));
}

TEST(QoraiAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithQoraiSchemeAndSyncHostNameAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://sync/foo")));
}

TEST(QoraiAdsUrlUtilInternalTest,
     ShouldSupportInternalUrlWithQoraiSchemeAndQoraAiHostName) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportInternalUrl(GURL("chrome://qora-ai")));
}

TEST(QoraiAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithQoraiSchemeAndQoraAiHostNameAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://qora-ai/foo")));
}

TEST(QoraiAdsUrlUtilInternalTest,
     ShouldSupportInternalUrlWithQoraiSchemeAndRewardsHostName) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportInternalUrl(GURL("chrome://rewards")));
}

TEST(QoraiAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithQoraiSchemeAndRewardsHostNameAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://rewards/foo")));
}

TEST(QoraiAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithQoraiSchemeAndSettingsHostName) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://settings")));
}

TEST(
    QoraiAdsUrlUtilInternalTest,
    ShouldNotSupportInternalUrlWithQoraiSchemeAndSettingsHostNameAndFooBarPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://settings/foobar")));
}

TEST(
    QoraiAdsUrlUtilInternalTest,
    ShouldSupportInternalUrlWithQoraiSchemeAndSettingsHostNameAndSurveyPanelistPath) {
  // Act & Assert
  EXPECT_TRUE(
      ShouldSupportInternalUrl(GURL("chrome://settings/surveyPanelist")));
}

TEST(
    QoraiAdsUrlUtilInternalTest,
    ShouldSupportInternalUrlWithQoraiSchemeAndSettingsHostNameAndSearchEnginesPath) {
  // Act & Assert
  EXPECT_TRUE(
      ShouldSupportInternalUrl(GURL("chrome://settings/searchEngines")));
}

TEST(
    QoraiAdsUrlUtilInternalTest,
    ShouldSupportInternalUrlWithQoraiSchemeAndSettingsHostNameAndSearchEnginesDefaultSearchPath) {
  // Act & Assert
  EXPECT_TRUE(
      ShouldSupportInternalUrl(GURL("chrome://settings/search/defaultSearch")));
}

TEST(
    QoraiAdsUrlUtilInternalTest,
    ShouldSupportInternalUrlWithQoraiSchemeAndSettingsHostNameSearchEnginesPathAndSearchQuery) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportInternalUrl(
      GURL("chrome://settings/searchEngines?search=foobar")));
}

TEST(
    QoraiAdsUrlUtilInternalTest,
    ShouldNotSupportInternalUrlWithQoraiSchemeAndSettingsHostNameSearchEnginesPathAndMultipleSearchQueries) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(
      GURL("chrome://settings/searchEngines?search=foo&bar=baz")));
}

TEST(
    QoraiAdsUrlUtilInternalTest,
    ShouldNotSupportInternalUrlWithQoraiSchemeAndSettingsHostNameSearchEnginesPathAndInvalidQuery) {
  // Act & Assert
  EXPECT_FALSE(
      ShouldSupportInternalUrl(GURL("chrome://settings/searchEngines?search")));
}

TEST(QoraiAdsUrlUtilInternalTest,
     ShouldSupportInternalUrlWithQoraiSchemeAndSettingsHostNameAndSearchPath) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportInternalUrl(GURL("chrome://settings/search")));
}

TEST(
    QoraiAdsUrlUtilInternalTest,
    ShouldSupportInternalUrlWithQoraiSchemeAndSettingsHostNameSearchPathAndSearchQuery) {
  // Act & Assert
  EXPECT_TRUE(
      ShouldSupportInternalUrl(GURL("chrome://settings/search?search=foobar")));
}

TEST(
    QoraiAdsUrlUtilInternalTest,
    ShouldNotSupportInternalUrlWithQoraiSchemeAndSettingsHostNameSearchPathAndMultipleSearchQueries) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(
      GURL("chrome://settings/search?search=foo&bar=baz")));
}

TEST(
    QoraiAdsUrlUtilInternalTest,
    ShouldNotSupportInternalUrlWithQoraiSchemeAndSettingsHostNameSearchPathAndInvalidQuery) {
  // Act & Assert
  EXPECT_FALSE(
      ShouldSupportInternalUrl(GURL("chrome://settings/search?search")));
}

TEST(QoraiAdsUrlUtilInternalTest,
     ShouldNotSupportInternalUrlWithQoraiSchemeAndSettingsHostNameAndQuery) {
  // Act & Assert
  EXPECT_FALSE(
      ShouldSupportInternalUrl(GURL("chrome://settings/?search=foobar")));
}

TEST(
    QoraiAdsUrlUtilInternalTest,
    ShouldNotSupportInternalUrlWithQoraiSchemeAndSettingsHostNameAndInvalidQuery) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportInternalUrl(GURL("chrome://settings/?search")));
}

TEST(QoraiAdsUrlUtilInternalTest, ShouldNotSupportMalformedUrl) {
  // Act & Assert
  EXPECT_FALSE(
      ShouldSupportInternalUrl(GURL("http://foobar.com/chrome://wallet")));
}

}  // namespace qorai_ads::internal
