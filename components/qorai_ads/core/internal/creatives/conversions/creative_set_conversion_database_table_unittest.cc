/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/creatives/conversions/creative_set_conversion_database_table.h"

#include "base/run_loop.h"
#include "base/test/gmock_callback_support.h"
#include "base/test/mock_callback.h"
#include "qorai/components/qorai_ads/core/internal/ad_units/ad_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/creatives/conversions/creative_set_conversion_database_table_util.h"
#include "qorai/components/qorai_ads/core/internal/creatives/conversions/creative_set_conversion_test_util.h"
#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/types/verifiable_conversion/verifiable_conversion_test_constants.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsCreativeSetConversionDatabaseTableTest : public test::TestBase {
 protected:
  database::table::CreativeSetConversions database_table_;
};

TEST_F(QoraiAdsCreativeSetConversionDatabaseTableTest, EmptySave) {
  // Act
  database::SaveCreativeSetConversions({});

  // Assert
  base::MockCallback<database::table::GetCreativeSetConversionsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*success=*/true,
                            /*creative_set_conversions=*/::testing::IsEmpty()))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetUnexpired(callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeSetConversionDatabaseTableTest,
       SaveCreativeSetConversions) {
  // Arrange
  CreativeSetConversionList creative_set_conversions;

  const CreativeSetConversionInfo creative_set_conversion_1 =
      test::BuildVerifiableCreativeSetConversion(
          test::kCreativeSetId, /*url_pattern=*/"https://www.qorai.com/*",
          /*observation_window=*/base::Days(3),
          test::kVerifiableConversionAdvertiserPublicKeyBase64);
  creative_set_conversions.push_back(creative_set_conversion_1);

  const CreativeSetConversionInfo creative_set_conversion_2 =
      test::BuildCreativeSetConversion(
          test::kAnotherCreativeSetId,
          /*url_pattern=*/"https://www.qorai.com/signup/*",
          /*observation_window=*/base::Days(30));
  creative_set_conversions.push_back(creative_set_conversion_2);

  // Act
  database::SaveCreativeSetConversions(creative_set_conversions);

  // Assert
  base::MockCallback<database::table::GetCreativeSetConversionsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*success=*/true, creative_set_conversions))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetUnexpired(callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeSetConversionDatabaseTableTest,
       DoNotSaveDuplicateConversion) {
  // Arrange
  CreativeSetConversionList creative_set_conversions;

  const CreativeSetConversionInfo creative_set_conversion =
      test::BuildVerifiableCreativeSetConversion(
          test::kCreativeSetId, /*url_pattern=*/"https://www.qorai.com/*",
          /*observation_window=*/base::Days(3),
          test::kVerifiableConversionAdvertiserPublicKeyBase64);
  creative_set_conversions.push_back(creative_set_conversion);

  database::SaveCreativeSetConversions(creative_set_conversions);

  // Act
  database::SaveCreativeSetConversions(creative_set_conversions);

  // Assert
  base::MockCallback<database::table::GetCreativeSetConversionsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback, Run(/*success=*/true, creative_set_conversions))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetUnexpired(callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeSetConversionDatabaseTableTest,
       PurgeExpiredConversions) {
  // Arrange
  CreativeSetConversionList creative_set_conversions;

  const CreativeSetConversionInfo creative_set_conversion_1 =
      test::BuildCreativeSetConversion(
          test::kCreativeSetId,
          /*url_pattern=*/"https://www.qorai.com/*",
          /*observation_window=*/base::Days(7));
  creative_set_conversions.push_back(creative_set_conversion_1);

  const CreativeSetConversionInfo creative_set_conversion_2 =
      test::BuildCreativeSetConversion(
          test::kAnotherCreativeSetId,
          /*url_pattern=*/"https://www.qorai.com/signup/*",
          /*observation_window=*/base::Days(3));  // Should be purged
  creative_set_conversions.push_back(creative_set_conversion_2);

  database::SaveCreativeSetConversions(creative_set_conversions);

  AdvanceClockBy(base::Days(4));

  // Act
  database::PurgeExpiredCreativeSetConversions();

  // Assert
  base::MockCallback<database::table::GetCreativeSetConversionsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback,
              Run(/*success=*/true,
                  CreativeSetConversionList{creative_set_conversion_1}))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetUnexpired(callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeSetConversionDatabaseTableTest,
       SaveConversionWithMatchingCreativeSetIdAndType) {
  // Arrange
  CreativeSetConversionList creative_set_conversions_1;

  const CreativeSetConversionInfo creative_set_conversion_1 =
      test::BuildVerifiableCreativeSetConversion(
          test::kCreativeSetId,
          /*url_pattern=*/"https://www.qorai.com/1",
          /*observation_window=*/base::Days(3),
          test::kVerifiableConversionAdvertiserPublicKeyBase64);
  creative_set_conversions_1.push_back(creative_set_conversion_1);

  database::SaveCreativeSetConversions(creative_set_conversions_1);

  CreativeSetConversionList creative_set_conversions_2;

  const CreativeSetConversionInfo creative_set_conversion_2 =
      test::BuildVerifiableCreativeSetConversion(
          test::kCreativeSetId,
          /*url_pattern=*/"https://www.qorai.com/2",
          /*observation_window=*/base::Days(30),
          test::kVerifiableConversionAdvertiserPublicKeyBase64);
  creative_set_conversions_2.push_back(creative_set_conversion_2);

  // Act
  database::SaveCreativeSetConversions(creative_set_conversions_2);

  // Assert
  base::MockCallback<database::table::GetCreativeSetConversionsCallback>
      callback;
  base::RunLoop run_loop;
  EXPECT_CALL(callback,
              Run(/*success=*/true,
                  CreativeSetConversionList{creative_set_conversion_2}))
      .WillOnce(base::test::RunOnceClosure(run_loop.QuitClosure()));
  database_table_.GetUnexpired(callback.Get());
  run_loop.Run();
}

TEST_F(QoraiAdsCreativeSetConversionDatabaseTableTest, GetTableName) {
  // Act & Assert
  EXPECT_EQ("creative_set_conversions", database_table_.GetTableName());
}

}  // namespace qorai_ads
