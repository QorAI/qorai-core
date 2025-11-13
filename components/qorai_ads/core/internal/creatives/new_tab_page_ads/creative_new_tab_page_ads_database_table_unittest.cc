/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ads_database_table.h"

#include "base/run_loop.h"
#include "base/test/gmock_callback_support.h"
#include "base/test/mock_callback.h"
#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/mock_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/common/test/time_test_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_info.h"
#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_test_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/new_tab_page_ads/creative_new_tab_page_ad_wallpaper_type.h"
#include "qorai/components/qorai_ads/core/internal/segments/segment_alias.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsCreativeNewTabPageAdsDatabaseTableTest : public test::TestBase {
 protected:
  database::table::CreativeNewTabPageAds database_table_;
};

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest, SaveEmpty) {
  // Act
  test::SaveCreativeNewTabPageAds({});

  // Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*success=*/true, /*segments=*/::testing::IsEmpty(),
                            /*creative_ads=*/::testing::IsEmpty()))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForActiveCampaigns(callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest, Save) {
  // Arrange
  const CreativeNewTabPageAdList creative_ads =
      test::BuildCreativeNewTabPageAds(
          CreativeNewTabPageAdWallpaperType::kImage, /*count=*/2);

  // Act
  test::SaveCreativeNewTabPageAds(creative_ads);

  // Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*success=*/true,
                            SegmentList{"architecture", "arts & entertainment"},
                            ::testing::UnorderedElementsAreArray(creative_ads)))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForActiveCampaigns(callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest, SaveInBatches) {
  // Arrange
  database_table_.SetBatchSize(2);

  const CreativeNewTabPageAdList creative_ads =
      test::BuildCreativeNewTabPageAds(
          CreativeNewTabPageAdWallpaperType::kImage, /*count=*/3);

  // Act
  test::SaveCreativeNewTabPageAds(creative_ads);

  // Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*success=*/true,
                            SegmentList{"architecture", "arts & entertainment",
                                        "automotive"},
                            ::testing::UnorderedElementsAreArray(creative_ads)))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForActiveCampaigns(callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest, DoNotSaveDuplicates) {
  // Arrange
  const CreativeNewTabPageAdList creative_ads =
      test::BuildCreativeNewTabPageAds(
          CreativeNewTabPageAdWallpaperType::kImage, /*count=*/1);
  test::SaveCreativeNewTabPageAds(creative_ads);

  // Act
  test::SaveCreativeNewTabPageAds(creative_ads);

  // Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback,
              Run(/*success=*/true, SegmentList{"architecture"}, creative_ads))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForActiveCampaigns(callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest, GetForImageSegments) {
  // Arrange
  CreativeNewTabPageAdList creative_ads;

  CreativeNewTabPageAdInfo creative_ad_1 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*should_generate_random_uuids=*/true);
  creative_ad_1.segment = "food & drink";
  creative_ads.push_back(creative_ad_1);

  CreativeNewTabPageAdInfo creative_ad_2 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*should_generate_random_uuids=*/true);
  creative_ad_2.segment = "technology & computing";
  creative_ads.push_back(creative_ad_2);

  test::SaveCreativeNewTabPageAds(creative_ads);

  // Act & Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*success=*/true, SegmentList{"food & drink"},
                            CreativeNewTabPageAdList{creative_ad_1}))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForSegments(
      /*segments=*/{"food & drink"}, callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest,
       GetForSegmentsIfTypeIsRichMedia) {
  // Arrange
  CreativeNewTabPageAdList creative_ads;

  CreativeNewTabPageAdInfo creative_ad_1 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*should_generate_random_uuids=*/true);
  creative_ad_1.segment = "food & drink";
  creative_ads.push_back(creative_ad_1);

  CreativeNewTabPageAdInfo creative_ad_2 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*should_generate_random_uuids=*/true);
  creative_ad_2.segment = "technology & computing";
  creative_ads.push_back(creative_ad_2);

  test::SaveCreativeNewTabPageAds(creative_ads);

  // Act & Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*success=*/true, SegmentList{"food & drink"},
                            CreativeNewTabPageAdList{creative_ad_1}))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForSegments(
      /*segments=*/{"food & drink"}, callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest,
       DoNotGetForSegmentsIfTypeIsRichMediaAndJavascriptIsDisabled) {
  // Arrange
  test::MockAllowJavaScript(false);

  CreativeNewTabPageAdList creative_ads;

  CreativeNewTabPageAdInfo creative_ad_1 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*should_generate_random_uuids=*/true);
  creative_ad_1.segment = "food & drink";
  creative_ads.push_back(creative_ad_1);

  CreativeNewTabPageAdInfo creative_ad_2 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*should_generate_random_uuids=*/true);
  creative_ad_2.segment = "technology & computing";
  creative_ads.push_back(creative_ad_2);

  test::SaveCreativeNewTabPageAds(creative_ads);

  // Act & Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*success=*/true, SegmentList{"food & drink"},
                            /*creative_ads=*/::testing::IsEmpty()))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForSegments(
      /*segments=*/{"food & drink"}, callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest,
       DoNotGetForEmptySegments) {
  // Arrange
  CreativeNewTabPageAdList creative_ads;

  const CreativeNewTabPageAdInfo creative_ad_1 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*should_generate_random_uuids=*/true);
  creative_ads.push_back(creative_ad_1);

  const CreativeNewTabPageAdInfo creative_ad_2 =
      test::BuildCreativeNewTabPageAd(
          CreativeNewTabPageAdWallpaperType::kRichMedia,
          /*should_generate_random_uuids=*/true);
  creative_ads.push_back(creative_ad_2);

  test::SaveCreativeNewTabPageAds(creative_ads);

  // Act & Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*success=*/true,
                            /*segments=*/::testing::IsEmpty(),
                            /*creative_ads=*/::testing::IsEmpty()))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForSegments(/*segments=*/{}, callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest,
       DoNotGetForMissingSegment) {
  // Arrange
  const CreativeNewTabPageAdList creative_ads =
      test::BuildCreativeNewTabPageAds(
          CreativeNewTabPageAdWallpaperType::kImage, /*count=*/1);
  test::SaveCreativeNewTabPageAds(creative_ads);

  // Act & Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*success=*/true, SegmentList{"MISSING"},
                            /*creative_ads=*/::testing::IsEmpty()))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForSegments(
      /*segments=*/{"MISSING"}, callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest, GetForMultipleSegments) {
  // Arrange
  CreativeNewTabPageAdList creative_ads;

  CreativeNewTabPageAdInfo creative_ad_1 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*should_generate_random_uuids=*/true);
  creative_ad_1.segment = "technology & computing";
  creative_ads.push_back(creative_ad_1);

  CreativeNewTabPageAdInfo creative_ad_2 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*should_generate_random_uuids=*/true);
  creative_ad_2.segment = "food & drink";
  creative_ads.push_back(creative_ad_2);

  CreativeNewTabPageAdInfo creative_ad_3 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*should_generate_random_uuids=*/true);
  creative_ad_3.segment = "automotive";
  creative_ads.push_back(creative_ad_3);

  test::SaveCreativeNewTabPageAds(creative_ads);

  // Act & Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback,
              Run(/*success=*/true,
                  SegmentList{"technology & computing", "food & drink"},
                  ::testing::UnorderedElementsAreArray(
                      CreativeNewTabPageAdList{creative_ad_1, creative_ad_2})))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForSegments(
      /*segments=*/{"technology & computing", "food & drink"}, callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest,
       GetForCreativeInstanceIdIfTypeIsImage) {
  // Arrange
  CreativeNewTabPageAdList creative_ads;

  const CreativeNewTabPageAdInfo creative_ad_1 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*should_generate_random_uuids=*/true);
  creative_ads.push_back(creative_ad_1);

  const CreativeNewTabPageAdInfo creative_ad_2 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*should_generate_random_uuids=*/true);
  creative_ads.push_back(creative_ad_2);

  test::SaveCreativeNewTabPageAds(creative_ads);

  // Act & Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*success=*/true,
                            creative_ad_1.creative_instance_id, creative_ad_1))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForCreativeInstanceId(creative_ad_1.creative_instance_id,
                                           callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest,
       GetForCreativeInstanceIdIfTypeIsImageAndJavascriptIsDisabled) {
  // Arrange
  test::MockAllowJavaScript(false);

  CreativeNewTabPageAdList creative_ads;

  const CreativeNewTabPageAdInfo creative_ad_1 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*should_generate_random_uuids=*/true);
  creative_ads.push_back(creative_ad_1);

  const CreativeNewTabPageAdInfo creative_ad_2 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*should_generate_random_uuids=*/true);
  creative_ads.push_back(creative_ad_2);

  test::SaveCreativeNewTabPageAds(creative_ads);

  // Act & Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*success=*/true,
                            creative_ad_1.creative_instance_id, creative_ad_1))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForCreativeInstanceId(creative_ad_1.creative_instance_id,
                                           callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest,
       GetForCreativeInstanceIdIfTypeIsRichMedia) {
  // Arrange
  CreativeNewTabPageAdList creative_ads;

  const CreativeNewTabPageAdInfo creative_ad_1 =
      test::BuildCreativeNewTabPageAd(
          CreativeNewTabPageAdWallpaperType::kRichMedia,
          /*should_generate_random_uuids=*/true);
  creative_ads.push_back(creative_ad_1);

  const CreativeNewTabPageAdInfo creative_ad_2 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*should_generate_random_uuids=*/true);
  creative_ads.push_back(creative_ad_2);

  test::SaveCreativeNewTabPageAds(creative_ads);

  // Act & Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*success=*/true,
                            creative_ad_1.creative_instance_id, creative_ad_1))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForCreativeInstanceId(creative_ad_1.creative_instance_id,
                                           callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest,
       DoNotGetForCreativeInstanceIdIfTypeIsRichMediaAndJavascriptIsDisabled) {
  // Arrange
  test::MockAllowJavaScript(false);

  CreativeNewTabPageAdList creative_ads;

  const CreativeNewTabPageAdInfo creative_ad_1 =
      test::BuildCreativeNewTabPageAd(
          CreativeNewTabPageAdWallpaperType::kRichMedia,
          /*should_generate_random_uuids=*/true);
  creative_ads.push_back(creative_ad_1);

  const CreativeNewTabPageAdInfo creative_ad_2 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*should_generate_random_uuids=*/true);
  creative_ads.push_back(creative_ad_2);

  test::SaveCreativeNewTabPageAds(creative_ads);

  // Act & Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback,
              Run(/*success=*/false, creative_ad_1.creative_instance_id,
                  CreativeNewTabPageAdInfo{}))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForCreativeInstanceId(creative_ad_1.creative_instance_id,
                                           callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest,
       DoNotGetForMissingCreativeInstanceId) {
  // Arrange
  const CreativeNewTabPageAdList creative_ads =
      test::BuildCreativeNewTabPageAds(
          CreativeNewTabPageAdWallpaperType::kImage, /*count=*/1);
  test::SaveCreativeNewTabPageAds(creative_ads);

  // Act & Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdCallback> callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*success=*/false, test::kMissingCreativeInstanceId,
                            CreativeNewTabPageAdInfo{}))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForCreativeInstanceId(test::kMissingCreativeInstanceId,
                                           callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest,
       GetNonExpiredIfTypeIsImage) {
  // Arrange
  CreativeNewTabPageAdList creative_ads;

  CreativeNewTabPageAdInfo creative_ad_1 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*should_generate_random_uuids=*/true);
  creative_ad_1.start_at = test::DistantPast();
  creative_ad_1.end_at = test::Now();
  creative_ads.push_back(creative_ad_1);

  CreativeNewTabPageAdInfo creative_ad_2 =
      test::BuildCreativeNewTabPageAd(CreativeNewTabPageAdWallpaperType::kImage,
                                      /*should_generate_random_uuids=*/true);
  creative_ad_2.start_at = test::DistantPast();
  creative_ad_2.end_at = test::DistantFuture();
  creative_ads.push_back(creative_ad_2);

  test::SaveCreativeNewTabPageAds(creative_ads);

  AdvanceClockBy(base::Milliseconds(1));

  // Act & Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback,
              Run(/*success=*/true, SegmentList{creative_ad_2.segment},
                  CreativeNewTabPageAdList{creative_ad_2}))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForActiveCampaigns(callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest,
       GetNonExpiredIfTypeIsRichMedia) {
  // Arrange
  CreativeNewTabPageAdList creative_ads;

  CreativeNewTabPageAdInfo creative_ad_1 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*should_generate_random_uuids=*/true);
  creative_ad_1.start_at = test::DistantPast();
  creative_ad_1.end_at = test::Now();
  creative_ads.push_back(creative_ad_1);

  CreativeNewTabPageAdInfo creative_ad_2 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*should_generate_random_uuids=*/true);
  creative_ad_2.start_at = test::DistantPast();
  creative_ad_2.end_at = test::DistantFuture();
  creative_ads.push_back(creative_ad_2);

  test::SaveCreativeNewTabPageAds(creative_ads);

  AdvanceClockBy(base::Milliseconds(1));

  // Act & Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback,
              Run(/*success=*/true, SegmentList{creative_ad_2.segment},
                  CreativeNewTabPageAdList{creative_ad_2}))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForActiveCampaigns(callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest,
       DoNotGetNonExpiredIfTypeIsRichMediaAndJavascriptIsDisabled) {
  // Arrange
  test::MockAllowJavaScript(false);

  CreativeNewTabPageAdList creative_ads;

  CreativeNewTabPageAdInfo creative_ad_1 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*should_generate_random_uuids=*/true);
  creative_ad_1.start_at = test::DistantPast();
  creative_ad_1.end_at = test::Now();
  creative_ads.push_back(creative_ad_1);

  CreativeNewTabPageAdInfo creative_ad_2 = test::BuildCreativeNewTabPageAd(
      CreativeNewTabPageAdWallpaperType::kRichMedia,
      /*should_generate_random_uuids=*/true);
  creative_ad_2.start_at = test::DistantPast();
  creative_ad_2.end_at = test::DistantFuture();
  creative_ads.push_back(creative_ad_2);

  test::SaveCreativeNewTabPageAds(creative_ads);

  AdvanceClockBy(base::Milliseconds(1));

  // Act & Assert
  base::MockCallback<database::table::GetCreativeNewTabPageAdsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*success=*/true, /*segments=*/::testing::IsEmpty(),
                            /*creative_ads=*/::testing::IsEmpty()))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetForActiveCampaigns(callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeNewTabPageAdsDatabaseTableTest, GetTableName) {
  // Act & Assert
  EXPECT_EQ("creative_new_tab_page_ads", database_table_.GetTableName());
}

}  // namespace qorai_ads
