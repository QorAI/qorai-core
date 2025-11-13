/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_TEST_BASE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_TEST_BASE_H_

#include <memory>

#include "base/functional/callback.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/actions/conversion_action_types.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/conversions_observer_mock.h"

namespace qorai_ads {

class Conversions;
struct AdInfo;
struct VerifiableConversionInfo;

namespace test {

class QoraiAdsConversionsTestBase : public TestBase {
 public:
  QoraiAdsConversionsTestBase(const QoraiAdsConversionsTestBase&) = delete;
  QoraiAdsConversionsTestBase& operator=(const QoraiAdsConversionsTestBase&) =
      delete;

  ~QoraiAdsConversionsTestBase() override;

  // TestBase:
  void SetUp() override;
  void TearDown() override;

 protected:
  QoraiAdsConversionsTestBase();

  void VerifyOnDidConvertAdExpectation(
      const AdInfo& ad,
      ConversionActionType action_type,
      base::OnceClosure did_convert_ad_closure);

  void VerifyOnDidNotConvertAdExpectation();

  void VerifyOnDidConvertVerifiableAdExpectation(
      const AdInfo& ad,
      ConversionActionType action_type,
      const VerifiableConversionInfo& verifiable_conversion,
      base::OnceClosure did_convert_ad_closure);

  std::unique_ptr<Conversions> conversions_;

  ConversionsObserverMock conversions_observer_mock_;
};

}  // namespace test

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_CONVERSIONS_TEST_BASE_H_
