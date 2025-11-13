/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/public/common/url/url_util.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsUrlUtilTest, GetUrlExcludingQuery) {
  // Act & Assert
  EXPECT_EQ(GURL("https://foo.com/bar"),
            GetUrlExcludingQuery(GURL("https://foo.com/bar?baz=qux")));
}

TEST(QoraiAdsUrlUtilTest, GetUrlExcludingQueryWhenNoQueryNameAndValue) {
  // Act & Assert
  EXPECT_EQ(GURL("https://foo.com/bar"),
            GetUrlExcludingQuery(GURL("https://foo.com/bar?")));
}

TEST(QoraiAdsUrlUtilTest, GetUrlExcludingQueryWhenNoQuery) {
  // Act & Assert
  EXPECT_EQ(GURL("https://foo.com/bar"),
            GetUrlExcludingQuery(GURL("https://foo.com/bar")));
}

TEST(QoraiAdsUrlUtilTest, ShouldNotSupportInvalidUrl) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("some random string")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("//*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("://*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("*://*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("*****")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://?.com")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://?.google.com")));
}

TEST(QoraiAdsUrlUtilTest, ShouldNotSupportUrlWithNonHttpsScheme) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("*://www.example.com/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("http://www.example.com/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("ftp://www.example.com/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL(
      "ipfs://bafybeigi77rim3p5tw3upw2ca4ep5ng7uaarvrz46zidd2ai6cjh46yxoy/")));
  EXPECT_FALSE(ShouldSupportUrl(GURL(
      "ipfs://bafybeigi77rim3p5tw3upw2ca4ep5ng7uaarvrz46zidd2ai6cjh46yxoy/")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("javascript:alert(1)")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("data:text/html,<h1>hello</h1>")));
}

TEST(QoraiAdsUrlUtilTest, ShouldNotSupportUrlWithPortNumber) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://www.qorai.com:1234/thank-you*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://www.qorai.com:1234*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://qorai.com:*/x")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://qorai.com:*")));
}

TEST(QoraiAdsUrlUtilTest, ShouldNotSupportIpAddress) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://1.2.3.4/thank-you*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://192.168.0.0/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://192.*.*.*/x")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://[::1]/thankyou")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://030000001017/")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://0xc000020f/")));
}

TEST(QoraiAdsUrlUtilTest, ShouldNotSupportUrlWithUsernameOrPassword) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://user:pwd@qoranet.com/thank-you*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://user@qoranet.com:1234*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://*@qoranet.com/x")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://user:*@qoranet.com/y")));
}

TEST(QoraiAdsUrlUtilTest, ShouldNotSupportUrlWithWildcardInEtldPlus1) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://www.google.co.*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://www.google.*.uk")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://www.*.co.uk")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://www.google.co.uk*")));
  EXPECT_FALSE(
      ShouldSupportUrl(GURL("https://www.comparecredit.com*/secure*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://www.sophos.com*thank-you*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://*.security/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://*.appspot.com/*")));
}

TEST(QoraiAdsUrlUtilTest, ShouldNotSupportLocalUrl) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://localhost/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://example.local/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://*.example.local/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://*.local/*")));
  EXPECT_FALSE(ShouldSupportUrl(GURL("https://localhost*/")));
}

TEST(QoraiAdsUrlUtilTest, ShouldSupportUrl) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://*.google.co.uk")));
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://www.google.co.uk/*")));
  EXPECT_TRUE(
      ShouldSupportUrl(GURL("https://dashboard.0x.org/create-account/"
                            "verification-sent?tx-relay-qorai*")));
  EXPECT_TRUE(
      ShouldSupportUrl(GURL("https://www.app.apxlending.com/verify_email*")));
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://bonkmark.com/*/#send")));
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://account.qorai.com/account/*")));
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://www.cube.exchange/*step=5*")));
  EXPECT_TRUE(ShouldSupportUrl(GURL(
      "https://play.google.com/store/apps/details?id=com.musclewiki.macro*")));
  EXPECT_TRUE(ShouldSupportUrl(
      GURL("https://mail.proton.me/u/*/inbox?welcome=true&ref=*")));
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://sheets.new/*")));
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://*.hello.security/*")));
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://mysite.appspot.com/*")));
  EXPECT_TRUE(ShouldSupportUrl(GURL("https://my.site.developer.app/*")));
}

TEST(QoraiAdsUrlUtilTest, ShouldNotSupportQoraiSchemeWithFooBarHostName) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://foobar")));
}

TEST(QoraiAdsUrlUtilTest, ShouldSupportQoraiSchemeWithGettingStartedHostName) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("chrome://getting-started")));
}

TEST(QoraiAdsUrlUtilTest,
     ShouldNotSupportQoraiSchemeWithGettingStartedHostNameAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://getting-started/foo")));
}

TEST(QoraiAdsUrlUtilTest, ShouldSupportQoraiSchemeWithWalletHostName) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("chrome://wallet")));
}

TEST(QoraiAdsUrlUtilTest,
     ShouldNotSupportQoraiSchemeWithWalletHostNameAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://wallet/foo")));
}

TEST(QoraiAdsUrlUtilTest, ShouldSupportQoraiSchemeWithSyncHostName) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("chrome://sync")));
}

TEST(QoraiAdsUrlUtilTest, ShouldNotSupportQoraiSchemeWithSyncHostNameAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://sync/foo")));
}

TEST(QoraiAdsUrlUtilTest, ShouldSupportQoraiSchemeWithRewardsHostName) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("chrome://rewards")));
}

TEST(QoraiAdsUrlUtilTest,
     ShouldNotSupportQoraiSchemeWithRewardsHostNameAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://rewards/foo")));
}

TEST(QoraiAdsUrlUtilTest, ShouldSupportQoraiSchemeWithQoraAiHostName) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("chrome://qora-ai")));
}

TEST(QoraiAdsUrlUtilTest, ShouldNotSupportQoraiSchemeWithQoraAiHostNameAndPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://qora-ai/foo")));
}

TEST(QoraiAdsUrlUtilTest, ShouldNotSupportQoraiSchemeWithSettingsHostName) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://settings")));
}

TEST(QoraiAdsUrlUtilTest,
     ShouldNotSupportQoraiSchemeWithSettingsHostNameAndFooBarPath) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://settings/foobar")));
}

TEST(QoraiAdsUrlUtilTest,
     ShouldSupportQoraiSchemeWithSettingsHostNameAndSearchEnginesPath) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("chrome://settings/searchEngines")));
}

TEST(
    QoraiAdsUrlUtilTest,
    ShouldSupportQoraiSchemeWithSettingsHostNameSearchEnginesPathAndSearchQuery) {
  // Act & Assert
  EXPECT_TRUE(
      ShouldSupportUrl(GURL("chrome://settings/searchEngines?search=foobar")));
}

TEST(
    QoraiAdsUrlUtilTest,
    ShouldNotSupportQoraiSchemeWithSettingsHostNameSearchEnginesPathAndMultipleSearchQueries) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(
      GURL("chrome://settings/searchEngines?search=foo&bar=baz")));
}

TEST(
    QoraiAdsUrlUtilTest,
    ShouldNotSupportQoraiSchemeWithSettingsHostNameSearchEnginesPathAndInvalidQuery) {
  // Act & Assert
  EXPECT_FALSE(
      ShouldSupportUrl(GURL("chrome://settings/searchEngines?search")));
}

TEST(QoraiAdsUrlUtilTest,
     ShouldSupportQoraiSchemeWithSettingsHostNameAndSearchPath) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("chrome://settings/search")));
}

TEST(QoraiAdsUrlUtilTest,
     ShouldSupportQoraiSchemeWithSettingsHostNameSearchPathAndSearchQuery) {
  // Act & Assert
  EXPECT_TRUE(ShouldSupportUrl(GURL("chrome://settings/search?search=foobar")));
}

TEST(
    QoraiAdsUrlUtilTest,
    ShouldNotSupportQoraiSchemeWithSettingsHostNameSearchPathAndMultipleSearchQueries) {
  // Act & Assert
  EXPECT_FALSE(
      ShouldSupportUrl(GURL("chrome://settings/search?search=foo&bar=baz")));
}

TEST(QoraiAdsUrlUtilTest,
     ShouldNotSupportQoraiSchemeWithSettingsHostNameSearchPathAndInvalidQuery) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://settings/search?search")));
}

TEST(QoraiAdsUrlUtilTest,
     ShouldNotSupportQoraiSchemeWithSettingsHostNameAndQuery) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://settings/?search=foobar")));
}

TEST(QoraiAdsUrlUtilTest,
     ShouldNotSupportQoraiSchemeWithSettingsHostNameAndInvalidQuery) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("chrome://settings/?search")));
}

TEST(QoraiAdsUrlUtilTest, ShouldNotSupportMalformedUrl) {
  // Act & Assert
  EXPECT_FALSE(ShouldSupportUrl(GURL("http://foobar.com/chrome://wallet")));
}

TEST(QoraiAdsUrlUtilTest, UrlMatchesPatternWithNoWildcards) {
  // Act & Assert
  EXPECT_TRUE(MatchUrlPattern(GURL("https://www.foo.com/"),
                              /*pattern=*/"https://www.foo.com/"));
}

TEST(QoraiAdsUrlUtilTest, UrlWithPathMatchesPatternWithNoWildcards) {
  // Act & Assert
  EXPECT_TRUE(MatchUrlPattern(GURL("https://www.foo.com/bar"),
                              /*pattern=*/"https://www.foo.com/bar"));
}

TEST(QoraiAdsUrlUtilTest, UrlDoesNotMatchPattern) {
  // Act & Assert
  EXPECT_FALSE(
      MatchUrlPattern(GURL("https://www.foo.com/"), /*pattern=*/"www.foo.com"));
}

TEST(QoraiAdsUrlUtilTest, UrlMatchesPatternWithQuery) {
  // Act & Assert
  EXPECT_TRUE(
      MatchUrlPattern(GURL("https://dashboard.0x.org/create-account/"
                           "verification-sent?tx-relay-qorai-browser"),
                      /*pattern=*/"https://dashboard.0x.org/create-account/"
                                  "verification-sent?tx-relay-qorai*"));
}

TEST(QoraiAdsUrlUtilTest, UrlDoesNotMatchPatternWithQuery) {
  // Act & Assert
  EXPECT_FALSE(
      MatchUrlPattern(GURL("https://dashboard.0x.org/create-account/"
                           "verification-sent-tx-relay-qorai-browser"),
                      /*pattern=*/"https://dashboard.0x.org/create-account/"
                                  "verification-sent?tx-relay-qorai*"));
}

TEST(QoraiAdsUrlUtilTest, UrlDoesNotMatchPatternWithMissingEmptyPath) {
  // Act & Assert
  EXPECT_FALSE(MatchUrlPattern(GURL("https://www.foo.com/"),
                               /*pattern=*/"https://www.foo.com"));
}

TEST(QoraiAdsUrlUtilTest, UrlMatchesEndWildcardPattern) {
  // Act & Assert
  EXPECT_TRUE(MatchUrlPattern(GURL("https://www.foo.com/bar?key=test"),
                              /*pattern=*/"https://www.foo.com/bar*"));
}

TEST(QoraiAdsUrlUtilTest, UrlMatchesMidWildcardPattern) {
  // Act & Assert
  EXPECT_TRUE(MatchUrlPattern(GURL("https://www.foo.com/woo-bar-hoo"),
                              /*pattern=*/"https://www.foo.com/woo*hoo"));
}

TEST(QoraiAdsUrlUtilTest, UrlDoesNotMatchMidWildcardPattern) {
  // Act & Assert
  EXPECT_FALSE(MatchUrlPattern(GURL("https://www.foo.com/woo"),
                               /*pattern=*/"https://www.foo.com/woo*hoo"));
}

TEST(QoraiAdsUrlUtilTest, SameDomainOrHost) {
  // Act & Assert
  EXPECT_TRUE(SameDomainOrHost(GURL("https://foo.com?bar=test"),
                               GURL("https://subdomain.foo.com/bar")));
}

TEST(QoraiAdsUrlUtilTest, NotSameDomainOrHost) {
  // Act & Assert
  EXPECT_FALSE(SameDomainOrHost(GURL("https://foo.com?bar=test"),
                                GURL("https://subdomain.bar.com/foo")));
}

TEST(QoraiAdsUrlUtilTest, SameDomainOrHostForUrlWithNoSubdomain) {
  // Act & Assert
  EXPECT_TRUE(SameDomainOrHost(GURL("https://foo.com?bar=test"),
                               GURL("https://foo.com/bar")));
}

TEST(QoraiAdsUrlUtilTest, NotSameDomainOrHostForUrlWithNoSubdomain) {
  // Act & Assert
  EXPECT_FALSE(SameDomainOrHost(GURL("https://foo.com?bar=test"),
                                GURL("https://bar.com/foo")));
}

TEST(QoraiAdsUrlUtilTest, SameDomainOrHostForUrlWithRef) {
  // Act & Assert
  EXPECT_TRUE(SameDomainOrHost(GURL("https://foo.com?bar=test#ref"),
                               GURL("https://foo.com/bar")));
}

TEST(QoraiAdsUrlUtilTest, NotSameDomainOrHostForUrlWithRef) {
  // Act & Assert
  EXPECT_FALSE(SameDomainOrHost(GURL("https://foo.com?bar=test#ref"),
                                GURL("https://bar.com/foo")));
}

TEST(QoraiAdsUrlUtilTest, DomainOrHostExists) {
  // Arrange
  const std::vector<GURL> urls = {GURL("https://foo.com"),
                                  GURL("https://bar.com")};

  // Act & Assert
  EXPECT_TRUE(DomainOrHostExists(urls, GURL("https://bar.com/foo")));
}

TEST(QoraiAdsUrlUtilTest, DomainOrHostDoesNotExist) {
  // Arrange
  const std::vector<GURL> urls = {GURL("https://foo.com"),
                                  GURL("https://bar.com")};

  // Act & Assert
  EXPECT_FALSE(DomainOrHostExists(urls, GURL("https://baz.com/qux")));
}

}  // namespace qorai_ads
