/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/common/subdivision/url_request/subdivision_url_request_builder.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "url/gurl.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsSubdivisionUrlRequestBuilderTest : public test::TestBase {};

TEST_F(QoraiAdsSubdivisionUrlRequestBuilderTest, BuildUrl) {
  // Arrange
  GetSubdivisionUrlRequestBuilder url_request_builder;

  // Act
  const mojom::UrlRequestInfoPtr mojom_url_request =
      url_request_builder.Build();

  // Assert
  const mojom::UrlRequestInfoPtr expected_mojom_url_request =
      mojom::UrlRequestInfo::New();
  expected_mojom_url_request->url =
      GURL("https://geo.ads.qoraisoftware.com/v1/getstate");
  expected_mojom_url_request->method = mojom::UrlRequestMethodType::kGet;
  EXPECT_EQ(expected_mojom_url_request, mojom_url_request);
}

}  // namespace qorai_ads
