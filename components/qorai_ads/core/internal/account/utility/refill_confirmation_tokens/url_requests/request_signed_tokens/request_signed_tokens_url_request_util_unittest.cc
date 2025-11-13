/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/utility/refill_confirmation_tokens/url_requests/request_signed_tokens/request_signed_tokens_url_request_util.h"

#include "base/test/values_test_util.h"
#include "qorai/components/qorai_ads/core/internal/account/utility/refill_confirmation_tokens/refill_confirmation_tokens_test_util.h"
#include "qorai/components/qorai_ads/core/internal/account/utility/refill_confirmation_tokens/url_requests/get_signed_tokens/get_signed_tokens_url_request_builder_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsRequestSignedTokensUrlRequestUtilTest : public test::TestBase {};

TEST_F(QoraiAdsRequestSignedTokensUrlRequestUtilTest, ParseNonce) {
  // Act & Assert
  EXPECT_EQ(test::kRequestSignedTokensNonce,
            ParseNonce(base::test::ParseJsonDict(
                test::BuildRequestSignedTokensUrlResponseBody())));
}

TEST_F(QoraiAdsRequestSignedTokensUrlRequestUtilTest, DoNotParseMissingNonce) {
  // Act & Assert
  EXPECT_FALSE(ParseNonce({}));
}

}  // namespace qorai_ads
