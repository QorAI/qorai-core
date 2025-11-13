/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <string>

#include "base/strings/string_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/command_line_switch_test_info.h"
#include "qorai/components/qorai_ads/core/internal/common/test/command_line_switch_test_util.h"
#include "qorai/components/qorai_ads/core/internal/common/test/test_base.h"
#include "qorai/components/qorai_ads/core/internal/global_state/global_state.h"

// npm run test -- qorai_unit_tests --filter=QoraiAds*

namespace qorai_ads {

namespace {

struct ParamInfo final {
  test::CommandLineSwitchInfo command_line_switch;
  bool should_debug = false;
};

// TODO(https://github.com/qorai/qorai-browser/issues/48713): This is a case of
// `-Wexit-time-destructors` violation and `[[clang::no_destroy]]` has been
// added in the meantime to fix the build error. Remove this attribute and
// provide a proper fix.
[[clang::no_destroy]] const ParamInfo kTests[] = {
    {.command_line_switch = {"rewards", "debug=true"}, .should_debug = true},
    {.command_line_switch = {"rewards", "debug=1"}, .should_debug = true},
    {.command_line_switch = {"rewards", "debug=false"}, .should_debug = false},
    {.command_line_switch = {"rewards", "debug=foobar"}, .should_debug = false},
    {.command_line_switch = {}, .should_debug = false}};

}  // namespace

class QoraiAdsDebugCommandLineSwitchParserUtilTest
    : public test::TestBase,
      public ::testing::WithParamInterface<ParamInfo> {
 protected:
  void SetUpMocks() override {
    test::AppendCommandLineSwitches({GetParam().command_line_switch});
  }
};

TEST_P(QoraiAdsDebugCommandLineSwitchParserUtilTest,
       ParseDebugCommandLineSwitch) {
  // Act & Assert
  ASSERT_TRUE(GlobalState::HasInstance());
  EXPECT_EQ(GetParam().should_debug,
            GlobalState::GetInstance()->Flags().should_debug);
}

std::string TestParamToString(
    const ::testing::TestParamInfo<ParamInfo>& test_param) {
  const std::string should_debug =
      test_param.param.should_debug ? "ShouldDebug" : "ShouldNotDebug";

  const std::string sanitized_command_line_switch =
      test::ToString(test_param.param.command_line_switch);

  return base::ReplaceStringPlaceholders(
      "$1For$2", {should_debug, sanitized_command_line_switch}, nullptr);
}

INSTANTIATE_TEST_SUITE_P(,
                         QoraiAdsDebugCommandLineSwitchParserUtilTest,
                         ::testing::ValuesIn(kTests),
                         TestParamToString);

}  // namespace qorai_ads
