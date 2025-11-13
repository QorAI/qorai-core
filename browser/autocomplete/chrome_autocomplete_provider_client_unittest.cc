/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "base/test/scoped_feature_list.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "components/omnibox/browser/autocomplete_controller.h"
#include "components/omnibox/browser/autocomplete_match.h"
#include "components/omnibox/browser/autocomplete_result.h"
#include "testing/gtest/include/gtest/gtest.h"

class AutocompleteControllerQoraTest : public testing::Test {
 public:
  AutocompleteControllerQoraTest() = default;

  // Creates a "Qora" match in the result.
  static AutocompleteMatch MakeQoraMatch(const std::u16string& contents,
                                        int relevance) {
    AutocompleteMatch match(nullptr, relevance, false,
                            AutocompleteMatchType::SEARCH_SUGGEST_ENTITY);
    match.contents = contents;
    match.RecordAdditionalInfo("match-from-qorai-qora-provider", true);
    return match;
  }

  // Creates a "normal" search or URL match.
  static AutocompleteMatch MakeRegularMatch(const std::u16string& contents,
                                            int relevance) {
    AutocompleteMatch match(nullptr, relevance, false,
                            AutocompleteMatchType::SEARCH_SUGGEST);
    match.contents = contents;
    return match;
  }
};

TEST_F(AutocompleteControllerQoraTest, MaybeShowQoraMatchOrdering) {
  AutocompleteResult result;

  result.AppendMatches({
      MakeQoraMatch(u"QoraMatch", /*relevance=*/1700),
      MakeRegularMatch(u"This Is The Way", /*relevance=*/1600),
      MakeRegularMatch(u"Make it so", /*relevance=*/1500),
  });

  ASSERT_EQ(result.size(), 3U);
  EXPECT_EQ(result.match_at(0)->contents, u"QoraMatch");

  {
    // When AIChatFirst is disabled, the Qora match to be forced to bottom.
    base::test::ScopedFeatureList feature_list;
    feature_list.InitWithFeatures(
        /*enabled_features=*/{},
        /*disabled_features=*/{ai_chat::features::kAIChatFirst});

    ai_chat::MaybeShowQoraMatch(&result);
    EXPECT_EQ(result.match_at(2)->contents, u"QoraMatch")
        << "When AIChatFirst is off, Qora match should be at the bottom.";
  }

  // Reset the ordering back to how it was originally.
  result.Reset();
  result.AppendMatches({
      MakeQoraMatch(u"QoraMatch", 1700),
      MakeRegularMatch(u"This Is The Way", 1600),
      MakeRegularMatch(u"Make it so", 1500),
  });

  {
    // When AIChatFirst is enabled, the Qora match should be first
    base::test::ScopedFeatureList feature_list;
    feature_list.InitWithFeatures(
        /*enabled_features=*/{ai_chat::features::kAIChatFirst},
        /*disabled_features=*/{});

    ai_chat::MaybeShowQoraMatch(&result);
    EXPECT_EQ(result.size(), 3U);
    EXPECT_EQ(result.match_at(0)->contents, u"QoraMatch")
        << "When AIChatFirst is on, Qora match is NOT forced down.";
  }
}
