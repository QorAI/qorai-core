/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/net/search_ads_header_network_delegate_helper.h"

#include <memory>
#include <string_view>
#include <utility>

#include "base/test/scoped_feature_list.h"
#include "qorai/browser/net/url_context.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"
#include "qorai/components/qorai_rewards/core/pref_names.h"
#include "qorai/components/l10n/common/test/scoped_default_locale.h"
#include "chrome/browser/prefs/browser_prefs.h"
#include "chrome/test/base/testing_profile.h"
#include "components/prefs/pref_service.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "content/public/test/browser_task_environment.h"
#include "net/base/net_errors.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "third_party/blink/public/mojom/loader/resource_load_info.mojom-data-view.h"
#include "url/gurl.h"

#if BUILDFLAG(IS_ANDROID)
#include "qorai/components/qorai_rewards/core/features.h"
#endif  // BUILDFLAG(IS_ANDROID)

using testing::Return;

namespace qorai {

namespace {

constexpr std::string_view kQoraiSearchRequestUrl =
    "https://search.qorai.com/search?q=qwerty";
constexpr std::string_view kQoraiSearchImageRequestUrl =
    "https://search.qorai.com/img.png";
constexpr std::string_view kNonQoraiSearchRequestUrl =
    "https://qorai.com/search?q=qwerty";
constexpr std::string_view kQoraiSearchTabUrl = "https://search.qorai.com";
constexpr std::string_view kNonQoraiSearchTabUrl = "https://qorai.com";

}  // namespace

class SearchAdsHeaderDelegateHelperTest : public testing::Test {
 protected:
  void SetUp() override {
    scoped_feature_list_.InitWithFeatures(
        {
#if BUILDFLAG(IS_ANDROID)
            qorai_rewards::features::kQoraiRewards
#endif  // BUILDFLAG(IS_ANDROID)
        },
        {});

    TestingProfile::Builder builder;
    auto prefs =
        std::make_unique<sync_preferences::TestingPrefServiceSyncable>();
    RegisterUserProfilePrefs(prefs->registry());
    builder.SetPrefService(std::move(prefs));
    profile_ = builder.Build();
  }

  void EnableQoraiRewards() {
    // Disabled by default.
    profile_->GetPrefs()->SetBoolean(qorai_rewards::prefs::kEnabled, true);
  }

  void ConnectExternalQoraiRewardsWallet() {
    // Disconnected by default.
    profile_->GetPrefs()->SetString(qorai_rewards::prefs::kExternalWalletType,
                                    "connected");
  }

  void OptOutOfSearchResultAds() {
    // Opted-in by default.
    profile_->GetPrefs()->SetBoolean(
        qorai_ads::prefs::kOptedInToSearchResultAds, false);
  }

  std::shared_ptr<QoraiRequestInfo> MakeRequest(std::string_view url,
                                                TestingProfile* profile) {
    auto request = std::make_shared<QoraiRequestInfo>(GURL(url));
    request->request_url = GURL(kQoraiSearchTabUrl);
    request->tab_origin = GURL(kQoraiSearchTabUrl);
    request->initiator_url = GURL(kQoraiSearchTabUrl);
    request->resource_type = blink::mojom::ResourceType::kMainFrame;
    request->browser_context = profile;
    return request;
  }

  void VerifyHeaderExistsExpectation(
      std::shared_ptr<QoraiRequestInfo> request) {
    net::HttpRequestHeaders request_headers;
    const int result_code = OnBeforeStartTransaction_SearchAdsHeader(
        &request_headers, ResponseCallback(), request);
    EXPECT_EQ(result_code, net::OK);
    EXPECT_TRUE(request_headers.HasHeader(kSearchAdsHeader));
    EXPECT_EQ(request_headers.GetHeader(kSearchAdsHeader),
              kSearchAdsDisabledValue);
  }

  void VerifyMissingHeaderExpectation(
      std::shared_ptr<QoraiRequestInfo> request) {
    net::HttpRequestHeaders request_headers;
    const int result_code = OnBeforeStartTransaction_SearchAdsHeader(
        &request_headers, ResponseCallback(), request);
    EXPECT_EQ(result_code, net::OK);
    EXPECT_FALSE(request_headers.HasHeader(kSearchAdsHeader));
  }

  qorai_l10n::test::ScopedDefaultLocale scoped_locale_{"en_US"};
  content::BrowserTaskEnvironment task_environment_;
  base::test::ScopedFeatureList scoped_feature_list_;
  std::unique_ptr<TestingProfile> profile_;
};

TEST_F(SearchAdsHeaderDelegateHelperTest,
       HeaderShouldExistForMainFrameResource) {
  EnableQoraiRewards();
  OptOutOfSearchResultAds();

  auto request = MakeRequest(kQoraiSearchRequestUrl, profile_.get());
  request->resource_type = blink::mojom::ResourceType::kMainFrame;
  VerifyHeaderExistsExpectation(request);
}

TEST_F(SearchAdsHeaderDelegateHelperTest, HeaderShouldExistForXhrResource) {
  EnableQoraiRewards();
  OptOutOfSearchResultAds();

  auto request = MakeRequest(kQoraiSearchRequestUrl, profile_.get());
  request->resource_type = blink::mojom::ResourceType::kXhr;
  VerifyHeaderExistsExpectation(request);
}

TEST_F(SearchAdsHeaderDelegateHelperTest, HeaderShouldExistForImageResource) {
  EnableQoraiRewards();
  OptOutOfSearchResultAds();

  auto request = MakeRequest(kQoraiSearchImageRequestUrl, profile_.get());
  request->resource_type = blink::mojom::ResourceType::kImage;
  VerifyHeaderExistsExpectation(request);
}

TEST_F(SearchAdsHeaderDelegateHelperTest,
       HeaderShouldNotExistForDisallowedTabOriginHost) {
  EnableQoraiRewards();

  auto request = MakeRequest(kQoraiSearchRequestUrl, profile_.get());
  request->tab_origin = GURL();
  VerifyMissingHeaderExpectation(request);
}

TEST_F(SearchAdsHeaderDelegateHelperTest,
       HeaderShouldNotExistForDisallowedInitiatorUrlHost) {
  EnableQoraiRewards();

  auto request = MakeRequest(kQoraiSearchRequestUrl, profile_.get());
  request->initiator_url = GURL();
  VerifyMissingHeaderExpectation(request);
}

TEST_F(
    SearchAdsHeaderDelegateHelperTest,
    HeaderShouldNotExistForDisallowedTabOriginHostAndDisallowedInitiatorUrlHost) {
  EnableQoraiRewards();

  auto request = MakeRequest(kQoraiSearchRequestUrl, profile_.get());
  request->tab_origin = GURL();
  request->initiator_url = GURL();
  VerifyMissingHeaderExpectation(request);
}

TEST_F(SearchAdsHeaderDelegateHelperTest,
       HeaderShouldNotExistForNonSearchTabOrigin) {
  EnableQoraiRewards();

  auto request = MakeRequest(kQoraiSearchRequestUrl, profile_.get());
  request->tab_origin = GURL(kNonQoraiSearchTabUrl);
  VerifyMissingHeaderExpectation(request);
}

TEST_F(SearchAdsHeaderDelegateHelperTest,
       HeaderShouldNotExistForNonSearchInitiatorUrl) {
  EnableQoraiRewards();

  auto request = MakeRequest(kQoraiSearchRequestUrl, profile_.get());
  request->initiator_url = GURL(kNonQoraiSearchTabUrl);
  VerifyMissingHeaderExpectation(request);
}

TEST_F(SearchAdsHeaderDelegateHelperTest,
       HeaderShouldNotExistForNonSearchRequest) {
  EnableQoraiRewards();

  auto request = MakeRequest(kNonQoraiSearchRequestUrl, profile_.get());
  VerifyMissingHeaderExpectation(request);
}

TEST_F(SearchAdsHeaderDelegateHelperTest, HeaderShouldNotExistForIncognito) {
  EnableQoraiRewards();

  auto request =
      MakeRequest(kQoraiSearchRequestUrl,
                  TestingProfile::Builder().BuildIncognito(profile_.get()));
  VerifyMissingHeaderExpectation(request);
}

TEST_F(SearchAdsHeaderDelegateHelperTest,
       HeaderShouldNotExistForNonRewardsUser) {
  auto request = MakeRequest(kQoraiSearchRequestUrl, profile_.get());
  VerifyMissingHeaderExpectation(request);
}

TEST_F(SearchAdsHeaderDelegateHelperTest,
       HeaderShouldExistForDisconnectedRewardsUserOptedOutOfAds) {
  EnableQoraiRewards();
  OptOutOfSearchResultAds();

  auto request = MakeRequest(kQoraiSearchRequestUrl, profile_.get());
  VerifyHeaderExistsExpectation(request);
}

TEST_F(SearchAdsHeaderDelegateHelperTest,
       HeaderShouldNotExistForDisconnectedRewardsUserOptedInToAds) {
  EnableQoraiRewards();

  auto request = MakeRequest(kQoraiSearchRequestUrl, profile_.get());
  VerifyMissingHeaderExpectation(request);
}

TEST_F(SearchAdsHeaderDelegateHelperTest,
       HeaderShouldExistForConnectedRewardsUserOptedOutOfAds) {
  EnableQoraiRewards();
  ConnectExternalQoraiRewardsWallet();
  OptOutOfSearchResultAds();

  auto request = MakeRequest(kQoraiSearchRequestUrl, profile_.get());
  VerifyHeaderExistsExpectation(request);
}

TEST_F(SearchAdsHeaderDelegateHelperTest,
       HeaderShouldExistForConnectedRewardsUserOptedInToAds) {
  EnableQoraiRewards();
  ConnectExternalQoraiRewardsWallet();

  auto request = MakeRequest(kQoraiSearchRequestUrl, profile_.get());
  VerifyHeaderExistsExpectation(request);
}

}  // namespace qorai
