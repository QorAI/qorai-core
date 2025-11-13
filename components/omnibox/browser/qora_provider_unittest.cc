/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/omnibox/browser/qora_provider.h"

#include "base/memory/scoped_refptr.h"
#include "base/test/scoped_feature_list.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/omnibox/browser/qorai_fake_autocomplete_provider_client.h"
#include "components/omnibox/browser/autocomplete_input.h"
#include "components/omnibox/browser/test_scheme_classifier.h"
#include "testing/gtest/include/gtest/gtest.h"

class QoraEnabledAutocompleteProviderClient
    : public QorAIFakeAutocompleteProviderClient {
 public:
  QoraEnabledAutocompleteProviderClient() = default;
  ~QoraEnabledAutocompleteProviderClient() override = default;
  bool IsQoraProviderEnabled() override { return true; }
};

class QoraProviderTest : public testing::Test {
 public:
  QoraProviderTest() = default;
  ~QoraProviderTest() override = default;

 protected:
  QoraEnabledAutocompleteProviderClient provider_client_;
};

TEST_F(QoraProviderTest, AIChatFirstOnAndOff) {
  base::test::ScopedFeatureList feature_list;

  // Enable AIChat but not AIChatFirst
  {
    feature_list.InitWithFeatures(
        /*enabled_features=*/{ai_chat::features::kAIChat},
        /*disabled_features=*/{ai_chat::features::kAIChatFirst});

    auto qora_provider = base::MakeRefCounted<QoraProvider>(&provider_client_);

    AutocompleteInput input(u"test input", 0, metrics::OmniboxEventProto::OTHER,
                            TestSchemeClassifier());
    qora_provider->Start(input, /*minimal_changes=*/false);

    const auto& matches = qora_provider->matches();
    ASSERT_EQ(matches.size(), 1U)
        << "AIChat on, AIChatFirst off expect exactly 1 match.";

    // Because AIChatFirst is disabled, it should be 1500 relevance,
    // and not allowed_to_be_default.
    EXPECT_EQ(matches[0].relevance, 1500);
    EXPECT_FALSE(matches[0].allowed_to_be_default_match);
  }

  feature_list.Reset();

  // Enable both AIChat and AIChatFirst
  {
    feature_list.InitWithFeatures(
        /*enabled_features=*/{ai_chat::features::kAIChat,
                              ai_chat::features::kAIChatFirst},
        /*disabled_features=*/{});

    auto qora_provider = base::MakeRefCounted<QoraProvider>(&provider_client_);

    AutocompleteInput input(u"test input", 0, metrics::OmniboxEventProto::OTHER,
                            TestSchemeClassifier());
    qora_provider->Start(input, /*minimal_changes=*/false);

    const auto& matches = qora_provider->matches();
    ASSERT_EQ(matches.size(), 1U)
        << "(D) AIChat & AIChatFirst expect exactly 1 match.";
    EXPECT_EQ(matches[0].relevance, 2500);
    EXPECT_TRUE(matches[0].allowed_to_be_default_match);
  }
}
