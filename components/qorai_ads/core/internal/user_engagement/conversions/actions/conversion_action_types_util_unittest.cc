/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/actions/conversion_action_types_util.h"

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsConversionActionTypesUtilTest, ToViewThroughConversionActionType) {
  // Act & Assert
  EXPECT_EQ(ConversionActionType::kViewThrough,
            ToConversionActionType(mojom::ConfirmationType::kViewedImpression));
}

TEST(QoraiAdsConversionActionTypesUtilTest,
     ToClickThroughConversionActionType) {
  // Act & Assert
  EXPECT_EQ(ConversionActionType::kClickThrough,
            ToConversionActionType(mojom::ConfirmationType::kClicked));
}

TEST(QoraiAdsConversionActionTypesUtilTest,
     StringToViewThroughConversionActionType) {
  // Act & Assert
  EXPECT_EQ(ConversionActionType::kViewThrough, ToConversionActionType("view"));
}

TEST(QoraiAdsConversionActionTypesUtilTest,
     StringToClickThroughConversionActionType) {
  // Act & Assert
  EXPECT_EQ(ConversionActionType::kClickThrough,
            ToConversionActionType("click"));
}

TEST(QoraiAdsConversionActionTypesUtilTest,
     ViewThroughConversionActionTypeToString) {
  // Act & Assert
  EXPECT_EQ("view", ToString(ConversionActionType::kViewThrough));
}

TEST(QoraiAdsConversionActionTypesUtilTest,
     ClickThroughConversionActionTypeToString) {
  // Act & Assert
  EXPECT_EQ("click", ToString(ConversionActionType::kClickThrough));
}

}  // namespace qorai_ads
