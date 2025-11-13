/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/ad_units/creative_ad_cache.h"

#include <memory>

#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/creatives/search_result_ads/creative_search_result_ad_test_util.h"
#include "net/http/http_status_code.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsCreativeAdCacheTest : public test::TestBase {
 protected:
  void SetUp() override {
    test::TestBase::SetUp();

    creative_ad_cache_ = std::make_unique<CreativeAdCache>();
  }

  std::unique_ptr<CreativeAdCache> creative_ad_cache_;
};

TEST_F(QoraiAdsCreativeAdCacheTest, AddCreativeAd) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*should_generate_random_uuids=*/true);

  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);

  // Act
  creative_ad_cache_->MaybeAdd(test::kPlacementId, mojom_creative_ad->Clone());

  // Assert
  EXPECT_EQ(mojom_creative_ad,
            creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
                test::kPlacementId));
}

TEST_F(QoraiAdsCreativeAdCacheTest, DoNotAddCreativeAd) {
  // Arrange
  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);

  // Act
  creative_ad_cache_->MaybeAdd(test::kPlacementId,
                               mojom::CreativeSearchResultAdInfoPtr{});

  // Assert
  EXPECT_FALSE(
      creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
          test::kPlacementId));
}

TEST_F(QoraiAdsCreativeAdCacheTest, DoNotAddInvalidCreativeAd) {
  // Arrange
  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);

  CreativeAdVariant creative_ad_variant;

  // Act
  creative_ad_cache_->MaybeAdd(test::kPlacementId,
                               std::move(creative_ad_variant));

  // Assert
  EXPECT_FALSE(
      creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
          test::kPlacementId));
}

TEST_F(QoraiAdsCreativeAdCacheTest, DoNotAddCreativeAdForOccludedTab) {
  // Arrange
  CreativeAdVariant creative_ad_variant(
      test::BuildCreativeSearchResultAdWithConversion(
          /*should_generate_random_uuids=*/true));

  // Act
  creative_ad_cache_->MaybeAdd(test::kPlacementId,
                               std::move(creative_ad_variant));

  // Assert
  EXPECT_FALSE(
      creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
          test::kPlacementId));
}

TEST_F(QoraiAdsCreativeAdCacheTest, DoNotGetCreativeAdForMissingPlacementId) {
  // Arrange
  CreativeAdVariant creative_ad_variant(
      test::BuildCreativeSearchResultAdWithConversion(
          /*should_generate_random_uuids=*/true));

  // Act
  creative_ad_cache_->MaybeAdd(test::kPlacementId,
                               std::move(creative_ad_variant));

  // Assert
  EXPECT_FALSE(
      creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
          test::kMissingPlacementId));
}

TEST_F(QoraiAdsCreativeAdCacheTest, GetCreativeAdsAcrossMultipleTabs) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*should_generate_random_uuids=*/true);

  // Act
  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);
  creative_ad_cache_->MaybeAdd(test::kPlacementId, mojom_creative_ad->Clone());

  SimulateOpeningNewTab(/*tab_id=*/2,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);
  creative_ad_cache_->MaybeAdd(test::kAnotherPlacementId,
                               mojom_creative_ad->Clone());

  // Assert
  EXPECT_EQ(mojom_creative_ad,
            creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
                test::kPlacementId));
  EXPECT_EQ(mojom_creative_ad,
            creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
                test::kAnotherPlacementId));
}

TEST_F(QoraiAdsCreativeAdCacheTest, PurgePlacementsOnTabDidClose) {
  // Arrange
  const mojom::CreativeSearchResultAdInfoPtr mojom_creative_ad =
      test::BuildCreativeSearchResultAdWithConversion(
          /*should_generate_random_uuids=*/true);

  SimulateOpeningNewTab(/*tab_id=*/1,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);
  creative_ad_cache_->MaybeAdd(test::kPlacementId, mojom_creative_ad->Clone());

  SimulateOpeningNewTab(/*tab_id=*/2,
                        /*redirect_chain=*/{GURL("https://qorai.com")},
                        net::HTTP_OK);
  creative_ad_cache_->MaybeAdd(test::kAnotherPlacementId,
                               mojom_creative_ad->Clone());

  // Act
  SimulateClosingTab(/*tab_id=*/2);

  // Assert
  EXPECT_EQ(mojom_creative_ad,
            creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
                test::kPlacementId));
  EXPECT_FALSE(
      creative_ad_cache_->MaybeGet<mojom::CreativeSearchResultAdInfoPtr>(
          test::kAnotherPlacementId));
}

}  // namespace qorai_ads
