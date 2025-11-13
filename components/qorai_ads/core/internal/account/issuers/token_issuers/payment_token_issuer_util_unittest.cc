/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/issuers/token_issuers/payment_token_issuer_util.h"

#include "base/uuid.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/issuers_feature.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/issuers_info.h"
#include "qorai/components/qorai_ads/core/internal/account/issuers/token_issuers/token_issuer_info.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsPaymentsIssuerUtilTest : public test::TestBase {};

TEST_F(QoraiAdsPaymentsIssuerUtilTest, IsPaymentTokenIssuerValid) {
  // Arrange
  TokenIssuerInfo token_issuer;
  token_issuer.type = TokenIssuerType::kPayments;

  for (size_t i = 0; i < kMaximumTokenIssuerPublicKeys.Get(); ++i) {
    token_issuer.public_keys.insert(
        {/*public_key=*/base::Uuid::GenerateRandomV4().AsLowercaseString(),
         /*associated_value=*/0.1});
  }

  IssuersInfo issuers;
  issuers.token_issuers.push_back(token_issuer);

  // Act & Assert
  EXPECT_TRUE(IsPaymentTokenIssuerValid(issuers));
}

TEST_F(QoraiAdsPaymentsIssuerUtilTest, IsPaymentTokenIssuerInvalid) {
  // Arrange
  TokenIssuerInfo token_issuer;
  token_issuer.type = TokenIssuerType::kPayments;

  for (size_t i = 0; i < kMaximumTokenIssuerPublicKeys.Get() + 1; ++i) {
    token_issuer.public_keys.insert(
        {/*public_key=*/base::Uuid::GenerateRandomV4().AsLowercaseString(),
         /*associated_value=*/0.1});
  }

  IssuersInfo issuers;
  issuers.token_issuers.push_back(token_issuer);

  // Act & Assert
  EXPECT_FALSE(IsPaymentTokenIssuerValid(issuers));
}

}  // namespace qorai_ads
