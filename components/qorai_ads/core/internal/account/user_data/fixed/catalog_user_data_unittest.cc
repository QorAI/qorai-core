/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/user_data/fixed/catalog_user_data.h"

#include "base/test/values_test_util.h"
#include "qorai/components/qorai_ads/core/internal/catalog/catalog_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/catalog/catalog_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/settings/settings_test_util.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsCatalogUserDataTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    SetCatalogId(test::kCatalogId);
  }
};

TEST_F(QoraiAdsCatalogUserDataTest, BuildCatalogUserData) {
  // Act & Assert
  EXPECT_EQ(base::test::ParseJsonDict(
                R"JSON(
                    {
                      "catalog": [
                        {
                          "id": "29e5c8bc0ba319069980bb390d8e8f9b58c05a20"
                        }
                      ]
                    })JSON"),
            BuildCatalogUserData());
}

TEST_F(QoraiAdsCatalogUserDataTest,
       DoNotBuildCatalogUserDataForNonRewardsUser) {
  // Arrange
  test::DisableQoraiRewards();

  // Act & Assert
  EXPECT_THAT(BuildCatalogUserData(), ::testing::IsEmpty());
}

}  // namespace qorai_ads
