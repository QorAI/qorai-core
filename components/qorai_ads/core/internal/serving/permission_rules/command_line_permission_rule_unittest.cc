/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/command_line_permission_rule.h"

#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/global_state/global_state.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

class QoraiAdsCommandLinePermissionRuleTest : public test::TestBase {};

TEST_F(QoraiAdsCommandLinePermissionRuleTest,
       ShouldAllowIfDidNotOverrideCommandLineSwitchesForProduction) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());

  GlobalState::GetInstance()->Flags().environment_type =
      mojom::EnvironmentType::kProduction;

  GlobalState::GetInstance()->Flags().did_override_from_command_line = false;

  // Act & Assert
  EXPECT_TRUE(HasCommandLinePermission());
}

TEST_F(QoraiAdsCommandLinePermissionRuleTest,
       ShouldAllowIfDidNotOverrideCommandLineSwitchesForStaging) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());

  GlobalState::GetInstance()->Flags().environment_type =
      mojom::EnvironmentType::kStaging;

  GlobalState::GetInstance()->Flags().did_override_from_command_line = false;

  // Act & Assert
  EXPECT_TRUE(HasCommandLinePermission());
}

TEST_F(QoraiAdsCommandLinePermissionRuleTest,
       ShouldNotAllowIfDidOverrideCommandLineSwitchesForProduction) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());

  GlobalState::GetInstance()->Flags().environment_type =
      mojom::EnvironmentType::kProduction;

  GlobalState::GetInstance()->Flags().did_override_from_command_line = true;

  // Act & Assert
  EXPECT_FALSE(HasCommandLinePermission());
}

TEST_F(QoraiAdsCommandLinePermissionRuleTest,
       ShouldAllowIfDidOverrideCommandLineSwitchesForStaging) {
  // Arrange
  ASSERT_TRUE(GlobalState::HasInstance());

  GlobalState::GetInstance()->Flags().environment_type =
      mojom::EnvironmentType::kStaging;

  GlobalState::GetInstance()->Flags().did_override_from_command_line = true;

  // Act & Assert
  EXPECT_TRUE(HasCommandLinePermission());
}

}  // namespace qorai_ads
