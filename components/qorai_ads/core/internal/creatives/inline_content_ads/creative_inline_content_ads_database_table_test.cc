/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/creatives/inline_content_ads/creative_inline_content_ads_database_table.h"

#include "base/run_loop.h"
#include "base/test/gmock_callback_support.h"
#include "base/test/mock_callback.h"
#include "qorai/components/qorai_ads/core/internal/catalog/catalog_url_request_builder_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/mock_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "net/http/http_status_code.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsCreativeInlineContentAdsDatabaseTableIntegrationTest
    : public test::TestBase {
 protected:
  void SetUp() override { test::TestBase::SetUp(/*is_integration_test=*/true); }

  void SetUpMocks() override {
    const test::URLResponseMap url_responses = {
        {BuildCatalogUrlPath(),
         {{net::HTTP_OK, /*response_body=*/"/catalog.json"}}}};
    test::MockUrlResponses(ads_client_mock_, url_responses);
  }
};

TEST_F(QoraiAdsCreativeInlineContentAdsDatabaseTableIntegrationTest,
       GetForSegmentsAndDimensions) {
  // Arrange
  const database::table::CreativeInlineContentAds database_table;

  // Act & Assert
  base::RunLoop run_loop;
  base::MockCallback<database::table::GetCreativeInlineContentAdsCallback>
      callback;
  EXPECT_CALL(callback, Run(/*success=*/true,
                            /*segments=*/SegmentList{"technology & computing"},
                            /*creative_ads=*/::testing::SizeIs(1)))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table.GetForSegmentsAndDimensions(
      /*segments=*/{"technology & computing"}, /*dimensions=*/"200x100",
      callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeInlineContentAdsDatabaseTableIntegrationTest,
       GetForDimensions) {
  // Arrange
  const database::table::CreativeInlineContentAds database_table;

  // Act & Assert
  base::RunLoop run_loop;
  base::MockCallback<
      database::table::GetCreativeInlineContentAdsForDimensionsCallback>
      callback;
  EXPECT_CALL(callback, Run(/*success=*/true,
                            /*creative_ads=*/::testing::SizeIs(1)))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table.GetForDimensions("200x100", callback.Get());
  run_loop.Run();
}

}  // namespace qorai_ads
