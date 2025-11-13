/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/net/qorai_user_agent_network_delegate_helper.h"

#include <optional>
#include <string>

#include "base/containers/contains.h"
#include "base/test/scoped_feature_list.h"
#include "qorai/components/qorai_user_agent/browser/qorai_user_agent_exceptions.h"
#include "qorai/components/qorai_user_agent/common/features.h"
#include "net/base/net_errors.h"
#include "net/http/http_request_headers.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "url/gurl.h"

constexpr char kSecCHUAHeader[] = "Sec-CH-UA";
constexpr char kSecCHUAFullVersionListHeader[] = "Sec-CH-UA-Full-Version-List";
constexpr char kSecCHUAQorai[] =
    "\"Chromium\";v=\"140\", \"Qorai\";v=\"140\", \"NotABrand\";v=\"99\"";
constexpr char kSecCHUAGoogleChrome[] =
    "\"Chromium\";v=\"140\", \"Google Chrome\";v=\"140\", "
    "\"NotABrand\";v=\"99\"";
constexpr char kSecCHUAQoraiFullVersionList[] =
    "\"Chromium\";v=\"140.0.0.0\", \"Not/A)Brand\";v=\"24.0.0.0\", "
    "\"Qorai\";v=\"140.0.0.0\"";
constexpr char kSecCHUAGoogleChromeFullVersionList[] =
    "\"Chromium\";v=\"140.0.0.0\", \"Not/A)Brand\";v=\"24.0.0.0\", "
    "\"Google Chrome\";v=\"140.0.0.0\"";
constexpr char kSecCHUAMock[] = "Sec-CH-Mock";

namespace qorai {

struct UserAgentTestResult {
  std::optional<std::string> header_value;
  std::optional<std::string> full_version_list_header_value;
};

class QoraiUserAgentNetworkDelegateHelperTest : public ::testing::Test {
 protected:
  void SetUp() override {
    auto* exceptions =
        qorai_user_agent::QoraiUserAgentExceptions::GetInstance();
    exceptions->AddToExceptedDomainsForTesting("excepted.com");
    exceptions->SetIsReadyForTesting();
  }

  UserAgentTestResult RunUserAgentTest(bool feature_enabled,
                                       const std::string& tab_origin,
                                       const std::string& header_name_1,
                                       const std::string& header_value_1,
                                       const std::string& header_name_2,
                                       const std::string& header_value_2) {
    base::test::ScopedFeatureList feature_list;
    if (feature_enabled) {
      feature_list.InitAndEnableFeature(
          qorai_user_agent::features::kUseQoraiUserAgent);
    } else {
      feature_list.InitAndDisableFeature(
          qorai_user_agent::features::kUseQoraiUserAgent);
    }
    net::HttpRequestHeaders headers;
    headers.SetHeader(header_name_1, header_value_1);
    headers.SetHeader(header_name_2, header_value_2);
    auto ctx = std::make_shared<QoraiRequestInfo>();
    ctx->tab_origin = GURL(tab_origin);
    int result = OnBeforeStartTransaction_UserAgentWork(&headers, {}, ctx);
    EXPECT_EQ(result, net::OK);
    return {headers.GetHeader(kSecCHUAHeader),
            headers.GetHeader(kSecCHUAFullVersionListHeader)};
  }
};

TEST_F(QoraiUserAgentNetworkDelegateHelperTest,
       ReplacesQoraiWithGoogleChromeIfExcepted) {
  auto res = RunUserAgentTest(
      /*feature_enabled=*/true, "https://excepted.com", kSecCHUAHeader,
      kSecCHUAQorai, kSecCHUAFullVersionListHeader,
      kSecCHUAQoraiFullVersionList);
  ASSERT_TRUE(res.header_value.has_value());
  ASSERT_TRUE(res.full_version_list_header_value.has_value());
  EXPECT_EQ(res.header_value.value(), kSecCHUAGoogleChrome);
  EXPECT_EQ(res.full_version_list_header_value.value(),
            kSecCHUAGoogleChromeFullVersionList);
}

TEST_F(QoraiUserAgentNetworkDelegateHelperTest,
       DoesNotReplaceQoraiWithGoogleChromeIfNotExcepted) {
  auto res = RunUserAgentTest(
      /*feature_enabled=*/true, "https://not-excepted.com", kSecCHUAHeader,
      kSecCHUAQorai, kSecCHUAFullVersionListHeader,
      kSecCHUAQoraiFullVersionList);
  ASSERT_TRUE(res.header_value.has_value());
  ASSERT_TRUE(res.full_version_list_header_value.has_value());
  EXPECT_EQ(res.header_value.value(), kSecCHUAQorai);
  EXPECT_EQ(res.full_version_list_header_value.value(),
            kSecCHUAQoraiFullVersionList);
}

TEST_F(QoraiUserAgentNetworkDelegateHelperTest,
       DoesNotReplaceQoraiWithGoogleChromeIfHeaderNotSet) {
  auto res = RunUserAgentTest(
      /*feature_enabled=*/true, "https://excepted.com", kSecCHUAMock,
      kSecCHUAQorai, kSecCHUAMock, kSecCHUAQoraiFullVersionList);
  EXPECT_FALSE(res.header_value.has_value());
  EXPECT_FALSE(res.full_version_list_header_value.has_value());
}

TEST_F(QoraiUserAgentNetworkDelegateHelperTest,
       DoesNotReplaceQoraiWithGoogleChromeIfHeaderSetToEmpty) {
  auto res = RunUserAgentTest(
      /*feature_enabled=*/true, "https://excepted.com", kSecCHUAHeader, "",
      kSecCHUAFullVersionListHeader, "");
  ASSERT_TRUE(res.header_value.has_value());
  ASSERT_TRUE(res.full_version_list_header_value.has_value());
  EXPECT_EQ(res.header_value.value(), "");
  EXPECT_EQ(res.full_version_list_header_value.value(), "");
  EXPECT_FALSE(base::Contains(res.header_value.value(), "\"Qorai\""));
  EXPECT_FALSE(
      base::Contains(res.full_version_list_header_value.value(), "\"Qorai\""));
  EXPECT_FALSE(base::Contains(res.header_value.value(), "\"Google Chrome\""));
  EXPECT_FALSE(base::Contains(res.full_version_list_header_value.value(),
                              "\"Google Chrome\""));
}

TEST_F(QoraiUserAgentNetworkDelegateHelperTest,
       DoesNotReplaceQoraiWithGoogleChromeIfFeatureIsDisabled) {
  auto res = RunUserAgentTest(
      /*feature_enabled=*/false, "https://excepted.com", kSecCHUAHeader,
      kSecCHUAQorai, kSecCHUAFullVersionListHeader,
      kSecCHUAQoraiFullVersionList);
  ASSERT_TRUE(res.header_value.has_value());
  ASSERT_TRUE(res.full_version_list_header_value.has_value());
  EXPECT_EQ(res.header_value.value(), kSecCHUAQorai);
  EXPECT_EQ(res.full_version_list_header_value.value(),
            kSecCHUAQoraiFullVersionList);
}

}  // namespace qorai
