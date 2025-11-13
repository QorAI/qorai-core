/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/catalog_permission_rule.h"

#include "qorai/components/qorai_ads/core/internal/catalog/catalog_url_request_builder_util.h"
#include "qorai/components/qorai_ads/core/internal/catalog/catalog_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/mock_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "net/http/http_status_code.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsCatalogPermissionRuleIntegrationTest : public test::TestBase {
 protected:
  void SetUp() override { test::TestBase::SetUp(/*is_integration_test=*/true); }

  void SetUpMocks() override {
    const test::URLResponseMap url_responses = {
        {BuildCatalogUrlPath(),
         {{net::HTTP_OK, /*response_body=*/"/catalog.json"}}}};
    test::MockUrlResponses(ads_client_mock_, url_responses);
  }
};

TEST_F(QoraiAdsCatalogPermissionRuleIntegrationTest, ShouldAllow) {
  // Act & Assert
  EXPECT_TRUE(HasCatalogPermission());
}

TEST_F(QoraiAdsCatalogPermissionRuleIntegrationTest,
       ShouldAllowIfCatalogWasLastUpdated23HoursAnd59MinutesAgo) {
  // Arrange
  AdvanceClockBy(base::Days(1) - base::Milliseconds(1));

  // Act & Assert
  EXPECT_TRUE(HasCatalogPermission());
}

TEST_F(QoraiAdsCatalogPermissionRuleIntegrationTest,
       ShouldNotAllowIfCatalogWasLastUpdated1DayAgo) {
  // Arrange
  AdvanceClockBy(base::Days(1));

  // Act & Assert
  EXPECT_FALSE(HasCatalogPermission());
}

TEST_F(QoraiAdsCatalogPermissionRuleIntegrationTest,
       ShouldNotAllowIfCatalogDoesNotExist) {
  // Arrange
  SetCatalogVersion(0);

  // Act & Assert
  EXPECT_FALSE(HasCatalogPermission());
}

}  // namespace qorai_ads
