/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/user_attention/user_idle_detection/user_idle_detection_util.h"

#include "base/test/scoped_feature_list.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/public/user_attention/user_idle_detection/user_idle_detection_feature.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsUserIdleDetectionUtilTest : public test::TestBase {};

TEST_F(QoraiAdsUserIdleDetectionUtilTest, WasLocked) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kUserIdleDetectionFeature, {{"should_detect_screen_was_locked", "true"}});

  // Act & Assert
  EXPECT_TRUE(MaybeScreenWasLocked(/*screen_was_locked=*/true));
}

TEST_F(QoraiAdsUserIdleDetectionUtilTest,
       WasLockedIfShouldDetectScreenWasLocked) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kUserIdleDetectionFeature, {{"should_detect_screen_was_locked", "true"}});

  // Act & Assert
  EXPECT_TRUE(MaybeScreenWasLocked(/*screen_was_locked=*/true));
}

TEST_F(QoraiAdsUserIdleDetectionUtilTest, WasNotLocked) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kUserIdleDetectionFeature, {{"should_detect_screen_was_locked", "true"}});

  // Act & Assert
  EXPECT_FALSE(MaybeScreenWasLocked(/*screen_was_locked=*/false));
}

TEST_F(QoraiAdsUserIdleDetectionUtilTest,
       WasNotLockedIfShouldNotDetectWasLocked) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kUserIdleDetectionFeature,
      {{"should_detect_screen_was_locked", "false"}});

  // Act & Assert
  EXPECT_FALSE(MaybeScreenWasLocked(/*screen_was_locked=*/true));
}

TEST_F(QoraiAdsUserIdleDetectionUtilTest, HasNotExceededMaximumIdleTime) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kUserIdleDetectionFeature, {{"maximum_idle_time", "10s"}});

  // Act & Assert
  EXPECT_FALSE(HasExceededMaximumIdleTime(base::Seconds(10)));
}

TEST_F(QoraiAdsUserIdleDetectionUtilTest,
       HasNotExceededInfiniteMaximumIdleTime) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kUserIdleDetectionFeature, {{"maximum_idle_time", "0s"}});

  // Act & Assert
  EXPECT_FALSE(HasExceededMaximumIdleTime(base::TimeDelta::Max()));
}

TEST_F(QoraiAdsUserIdleDetectionUtilTest, HasExceededMaximumIdleTime) {
  // Arrange
  base::test::ScopedFeatureList scoped_feature_list;
  scoped_feature_list.InitAndEnableFeatureWithParameters(
      kUserIdleDetectionFeature, {{"maximum_idle_time", "10s"}});

  // Act & Assert
  EXPECT_TRUE(HasExceededMaximumIdleTime(base::Seconds(11)));
}

}  // namespace qorai_ads
