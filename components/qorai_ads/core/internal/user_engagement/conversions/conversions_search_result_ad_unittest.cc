/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "base/time/time.h"
#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/conversions/creative_set_conversion_test_util.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_builder.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_test_util.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversions.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversions_test_base.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversions_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversions_test_util.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "qorai/components/qorai_ads/core/public/ad_units/ad_info.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsConversionsSearchResultAdTest
    : public test::QoraiAdsConversionsTestBase {};

TEST_F(QoraiAdsConversionsSearchResultAdTest,
       ConvertViewedAdIfOptedInToSearchResultAds) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*should_generate_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression});

  // Act & Assert
  base::RunLoop run_loop;
  VerifyOnDidConvertAdExpectation(ad, ConversionActionType::kViewThrough,
                                  run_loop.QuitClosure());
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain(),
                             /*html=*/"");
  run_loop.Run();
}

TEST_F(QoraiAdsConversionsSearchResultAdTest,
       DoNotConvertViewedAdIfOptedOutOfSearchResultAds) {
  // Arrange
  test::OptOutOfSearchResultAds();

  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*should_generate_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression});

  // Act & Assert
  VerifyOnDidNotConvertAdExpectation();
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain(),
                             /*html=*/"");
}

TEST_F(QoraiAdsConversionsSearchResultAdTest,
       ConvertClickedAdIfOptedInToSearchResultAds) {
  // Arrange
  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*should_generate_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression,
                            mojom::ConfirmationType::kClicked});

  // Act & Assert
  base::RunLoop run_loop;
  VerifyOnDidConvertAdExpectation(ad, ConversionActionType::kClickThrough,
                                  run_loop.QuitClosure());
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain(),
                             /*html=*/"");
  run_loop.Run();
}

TEST_F(QoraiAdsConversionsSearchResultAdTest,
       DoNotConvertClickedAdIfOptedOutOfSearchResultAds) {
  // Arrange
  test::OptOutOfSearchResultAds();

  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*should_generate_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));
  test::RecordAdEvents(ad, {mojom::ConfirmationType::kServedImpression,
                            mojom::ConfirmationType::kViewedImpression,
                            mojom::ConfirmationType::kClicked});

  // Act & Assert
  VerifyOnDidNotConvertAdExpectation();
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain(),
                             /*html=*/"");
}

TEST_F(QoraiAdsConversionsSearchResultAdTest,
       DoNotConvertViewedAdForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*should_generate_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));

  // We do not record ad events for non-Rewards users.
  test::RecordAdEvents(ad, /*mojom_confirmation_types=*/{});

  // Act & Assert
  VerifyOnDidNotConvertAdExpectation();
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain(),
                             /*html=*/"");
}

TEST_F(QoraiAdsConversionsSearchResultAdTest,
       ConvertClickedAdForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  const AdInfo ad = test::BuildAd(mojom::AdType::kSearchResultAd,
                                  /*should_generate_random_uuids=*/false);
  test::BuildAndSaveCreativeSetConversion(ad.creative_set_id,
                                          test::kMatchingUrlPattern,
                                          /*observation_window=*/base::Days(3));

  // We only record ad clicked and conversion events for non-Rewards users.
  test::RecordAdEvent(ad, mojom::ConfirmationType::kClicked);

  // Act & Assert
  base::RunLoop run_loop;
  VerifyOnDidConvertAdExpectation(ad, ConversionActionType::kClickThrough,
                                  run_loop.QuitClosure());
  conversions_->MaybeConvert(test::BuildDefaultConversionRedirectChain(),
                             /*html=*/"");
  run_loop.Run();
}

}  // namespace qorai_ads
