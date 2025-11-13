/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_feature.h"

#include "base/time/time.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

TEST(QoraiAdsPurchaseIntentFeatureTest, IsEnabled) {
  // Act & Assert
  EXPECT_TRUE(base::FeatureList::IsEnabled(kPurchaseIntentFeature));
}

TEST(QoraiAdsPurchaseIntentFeatureTest, PurchaseIntentResourceVersion) {
  // Act & Assert
  EXPECT_EQ(1, kPurchaseIntentResourceVersion.Get());
}

TEST(QoraiAdsPurchaseIntentFeatureTest, PurchaseIntentThreshold) {
  // Act & Assert
  EXPECT_EQ(3, kPurchaseIntentThreshold.Get());
}

TEST(QoraiAdsPurchaseIntentFeatureTest, PurchaseIntentTimeWindow) {
  // Act & Assert
  EXPECT_EQ(base::Days(7), kPurchaseIntentTimeWindow.Get());
}

}  // namespace qorai_ads
