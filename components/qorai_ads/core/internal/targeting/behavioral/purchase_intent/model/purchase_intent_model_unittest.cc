/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/model/purchase_intent_model.h"

#include <memory>

#include "qorai/components/qorai_ads/core/internal/common/resources/country_components_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/purchase_intent_processor.h"
#include "qorai/components/qorai_ads/core/internal/targeting/behavioral/purchase_intent/resource/purchase_intent_resource.h"
#include "url/gurl.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsPurchaseIntentModelTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    resource_ = std::make_unique<PurchaseIntentResource>();
  }

  std::unique_ptr<PurchaseIntentResource> resource_;
};

TEST_F(QoraiAdsPurchaseIntentModelTest,
       DoNotGetSegmentsForUnitializedResource) {
  // Arrange
  PurchaseIntentProcessor processor(*resource_);
  processor.Process(GURL("https://www.qorai.com/test?foo=bar"));

  // Act
  const SegmentList purchase_intent_segments = GetPurchaseIntentSegments();

  // Assert
  EXPECT_THAT(purchase_intent_segments, ::testing::IsEmpty());
}

TEST_F(QoraiAdsPurchaseIntentModelTest, DoNotGetSegmentsForExpiredSignals) {
  // Arrange
  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  PurchaseIntentProcessor processor(*resource_);
  processor.Process(GURL("https://www.qorai.com/test?foo=bar"));

  AdvanceClockBy(base::Days(1));

  processor.Process(GURL("https://www.basicattentiontoken.org/test?bar=foo"));

  // Act
  const SegmentList purchase_intent_segments = GetPurchaseIntentSegments();

  // Assert
  EXPECT_THAT(purchase_intent_segments, ::testing::IsEmpty());
}

TEST_F(QoraiAdsPurchaseIntentModelTest, DoNotGetSegmentsIfNeverProcessed) {
  // Arrange
  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  // Act
  const SegmentList purchase_intent_segments = GetPurchaseIntentSegments();

  // Assert
  EXPECT_THAT(purchase_intent_segments, ::testing::IsEmpty());
}

TEST_F(QoraiAdsPurchaseIntentModelTest,
       DoNotGetSegmentsIfNeverMatchedFunnelSites) {
  // Arrange
  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  PurchaseIntentProcessor processor(*resource_);
  processor.Process(GURL("https://duckduckgo.com/?q=segment+keyword+1"));

  // Act
  const SegmentList purchase_intent_segments = GetPurchaseIntentSegments();

  // Assert
  EXPECT_THAT(purchase_intent_segments, ::testing::IsEmpty());
}

TEST_F(QoraiAdsPurchaseIntentModelTest, GetSegmentsForPreviouslyMatchedSite) {
  // Arrange
  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  PurchaseIntentProcessor processor(*resource_);
  processor.Process(GURL("https://www.qorai.com/test?foo=bar"));
  processor.Process(GURL("https://basicattentiontoken.org/test?bar=foo"));
  processor.Process(GURL("https://www.qorai.com/test?foo=bar"));

  // Act
  const SegmentList purchase_intent_segments = GetPurchaseIntentSegments();

  // Assert
  const SegmentList expected_purchase_intent_segments = {"segment 3",
                                                         "segment 2"};
  EXPECT_EQ(expected_purchase_intent_segments, purchase_intent_segments);
}

TEST_F(QoraiAdsPurchaseIntentModelTest,
       GetSegmentsForPreviouslyMatchedSegmentKeyphrases) {
  // Arrange
  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  const GURL url = GURL("https://duckduckgo.com/?q=segment+keyword+1&foo=bar");

  PurchaseIntentProcessor processor(*resource_);
  processor.Process(url);
  processor.Process(url);
  processor.Process(url);

  // Act
  const SegmentList purchase_intent_segments = GetPurchaseIntentSegments();

  // Assert
  const SegmentList expected_purchase_intent_segments = {"segment 1"};
  EXPECT_EQ(expected_purchase_intent_segments, purchase_intent_segments);
}

TEST_F(QoraiAdsPurchaseIntentModelTest,
       GetSegmentsForPreviouslyMatchedFunnelKeywords) {
  // Arrange
  NotifyResourceComponentDidChange(test::kCountryComponentManifestVersion,
                                   test::kCountryComponentId);
  ASSERT_TRUE(resource_->IsLoaded());

  PurchaseIntentProcessor processor(*resource_);
  processor.Process(
      GURL("https://duckduckgo.com/?q=segment+keyword+1+funnel+keyword+2"));

  // Act
  const SegmentList purchase_intent_segments = GetPurchaseIntentSegments();

  // Assert
  const SegmentList expected_purchase_intent_segments = {"segment 1"};
  EXPECT_EQ(expected_purchase_intent_segments, purchase_intent_segments);
}

}  // namespace qorai_ads
