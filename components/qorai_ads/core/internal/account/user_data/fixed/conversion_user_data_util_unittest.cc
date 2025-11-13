/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_data/fixed/conversion_user_data_util.h"

#include <optional>
#include <string>

#include "base/json/json_writer.h"
#include "base/test/values_test_util.h"
#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_info.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversion/conversion_builder.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversion/conversion_info.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/types/verifiable_conversion/verifiable_conversion_info.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/types/verifiable_conversion/verifiable_conversion_test_constants.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_ads/core/public/ad_units/ad_info.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsConversionUserDataUtilTest : public test::TestBase {};

TEST_F(QoraiAdsConversionUserDataUtilTest, BuildVerifiableConversionUserData) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());
  const ConversionInfo conversion = BuildConversion(
      ad_event, VerifiableConversionInfo{
                    test::kVerifiableConversionId,
                    test::kVerifiableConversionAdvertiserPublicKeyBase64});

  // Act
  std::optional<base::Value::Dict> verifiable_conversion_user_data =
      MaybeBuildVerifiableConversionUserData(conversion);
  ASSERT_TRUE(verifiable_conversion_user_data);

  // Assert
  std::string json;
  ASSERT_TRUE(base::JSONWriter::Write(*verifiable_conversion_user_data, &json));

  EXPECT_THAT(
      json,
      ::testing::MatchesRegex(
          R"({"envelope":{"alg":"crypto_box_curve25519xsalsa20poly1305","ciphertext":".{64}","epk":".{44}","nonce":".{32}"}})"));
}

TEST_F(QoraiAdsConversionUserDataUtilTest,
       DoNotBuildVerifiableConversionUserData) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());
  const ConversionInfo conversion =
      BuildConversion(ad_event, /*verifiable_conversion=*/std::nullopt);

  // Act & Assert
  EXPECT_FALSE(MaybeBuildVerifiableConversionUserData(conversion));
}

TEST_F(QoraiAdsConversionUserDataUtilTest,
       DoNotBuildVerifiableConversionUserDataForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());
  const ConversionInfo conversion = BuildConversion(
      ad_event, VerifiableConversionInfo{
                    test::kVerifiableConversionId,
                    test::kVerifiableConversionAdvertiserPublicKeyBase64});

  // Act & Assert
  EXPECT_FALSE(MaybeBuildVerifiableConversionUserData(conversion));
}

TEST_F(QoraiAdsConversionUserDataUtilTest, BuildConversionActionTypeUserData) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kNotificationAd,
                                  /*should_generate_random_uuids=*/false);
  const AdEventInfo ad_event =
      BuildAdEvent(ad, mojom::ConfirmationType::kViewedImpression,
                   /*created_at=*/test::Now());
  const ConversionInfo conversion =
      BuildConversion(ad_event, /*verifiable_conversion=*/std::nullopt);

  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "action": "view"
                    })JSON"),
            BuildConversionActionTypeUserData(conversion));
}

}  // namespace qorai_ads
