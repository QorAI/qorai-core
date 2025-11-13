/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversions_test_base.h"

#include <utility>

#include "base/test/gmock_callback_support.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/ad_events/ad_event_test_util.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversion/conversion_info.h"  // IWYU pragma: keep
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversions.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/types/verifiable_conversion/verifiable_conversion_info.h"
#include "qorai/components/qorai_ads/core/public/ad_units/ad_info.h"

namespace qorai_ads::test {

QoraiAdsConversionsTestBase::QoraiAdsConversionsTestBase() = default;

QoraiAdsConversionsTestBase::~QoraiAdsConversionsTestBase() = default;

void QoraiAdsConversionsTestBase::SetUp() {
  TestBase::SetUp();

  conversions_ = std::make_unique<Conversions>();
  conversions_->AddObserver(&conversions_observer_mock_);
}

void QoraiAdsConversionsTestBase::TearDown() {
  conversions_->RemoveObserver(&conversions_observer_mock_);

  TestBase::TearDown();
}

void QoraiAdsConversionsTestBase::VerifyOnDidConvertAdExpectation(
    const AdInfo& ad,
    ConversionActionType action_type,
    base::OnceClosure did_convert_ad_closure) {
  EXPECT_CALL(conversions_observer_mock_,
              OnDidConvertAd(/*conversion=*/::testing::FieldsAre(
                  ad.type, ad.creative_instance_id, ad.creative_set_id,
                  ad.campaign_id, ad.advertiser_id, ad.segment, action_type,
                  /*verifiable*/ std::nullopt)))
      .WillOnce(base::test::RunOnceClosure(std::move(did_convert_ad_closure)));
}

void QoraiAdsConversionsTestBase::VerifyOnDidNotConvertAdExpectation() {
  EXPECT_CALL(conversions_observer_mock_, OnDidConvertAd).Times(0);
}

void QoraiAdsConversionsTestBase::VerifyOnDidConvertVerifiableAdExpectation(
    const AdInfo& ad,
    ConversionActionType action_type,
    const VerifiableConversionInfo& verifiable_conversion,
    base::OnceClosure did_convert_ad_closure) {
  EXPECT_CALL(
      conversions_observer_mock_,
      OnDidConvertAd(/*conversion=*/::testing::FieldsAre(
          ad.type, ad.creative_instance_id, ad.creative_set_id, ad.campaign_id,
          ad.advertiser_id, ad.segment, action_type, verifiable_conversion)))
      .WillOnce(base::test::RunOnceClosure(std::move(did_convert_ad_closure)));
}

}  // namespace qorai_ads::test
