/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "base/test/task_environment.h"
#include "components/omnibox/browser/autocomplete_input.h"
#include "components/omnibox/browser/autocomplete_match.h"
#include "components/omnibox/browser/autocomplete_match_type.h"
#include "components/omnibox/browser/autocomplete_result.h"
#include "components/omnibox/browser/fake_autocomplete_provider_client.h"
#include "components/omnibox/browser/featured_search_provider.h"
#include "components/omnibox/browser/test_scheme_classifier.h"
#include "components/search_engines/template_url.h"
#include "components/search_engines/template_url_data.h"
#include "components/search_engines/template_url_service.h"
#include "components/search_engines/template_url_starter_pack_data.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "third_party/metrics_proto/omnibox_event.pb.h"
#include "url/gurl.h"

namespace {

constexpr char16_t kAskQorAISearchKeyword[] = u"@ask";

const auto* kBookmarksUrl =
    template_url_starter_pack_data::bookmarks.destination_url;
const auto* kHistoryUrl =
    template_url_starter_pack_data::history.destination_url;
const auto* kTabsUrl = template_url_starter_pack_data::tabs.destination_url;
const auto* kAskQorAISearchUrl =
    template_url_starter_pack_data::ask_qorai_search.destination_url;

struct TestData {
  const std::u16string input;
  const std::vector<std::string> output;
};

}  // namespace

class QorAIFeaturedSearchProviderTest : public testing::Test {
 public:
  QorAIFeaturedSearchProviderTest(const QorAIFeaturedSearchProviderTest&) =
      delete;
  QorAIFeaturedSearchProviderTest& operator=(
      const QorAIFeaturedSearchProviderTest&) = delete;

 protected:
  QorAIFeaturedSearchProviderTest() = default;
  ~QorAIFeaturedSearchProviderTest() override = default;

  void SetUp() override {
    client_ = std::make_unique<FakeAutocompleteProviderClient>();
    provider_ = base::MakeRefCounted<FeaturedSearchProvider>(client_.get());
  }

  void RunTest(const std::vector<TestData>& test_cases) {
    for (const auto& test_case : test_cases) {
      AutocompleteInput input(test_case.input,
                              metrics::OmniboxEventProto::OTHER,
                              TestSchemeClassifier());

      input.set_allow_exact_keyword_match(false);
      provider_->Start(input, false);
      EXPECT_TRUE(provider_->done());
      auto matches = provider_->matches();
      ASSERT_EQ(test_case.output.size(), matches.size());
      for (size_t i = 0; i < test_case.output.size(); ++i) {
        EXPECT_EQ(matches[i].destination_url, GURL(test_case.output[i]));
      }
    }
  }

  base::test::TaskEnvironment task_environment_;
  std::unique_ptr<MockAutocompleteProviderClient> client_;
  scoped_refptr<FeaturedSearchProvider> provider_;
};

TEST_F(QorAIFeaturedSearchProviderTest, QorAIStarterPacks) {
  std::vector<std::unique_ptr<TemplateURLData>> turls =
      template_url_starter_pack_data::GetStarterPackEngines();
  for (auto& turl : turls) {
    client_->GetTemplateURLService()->Add(
        std::make_unique<TemplateURL>(std::move(*turl)));
  }

  std::vector<TestData> typing_scheme_cases = {
      // Typing the keyword without '@' or past the keyword shouldn't produce
      // results.
      {u"ask", {}},
      {u"@askk", {}},

      // Typing '@' should give all the starter pack suggestions.
      {u"@", {kAskQorAISearchUrl, kBookmarksUrl, kHistoryUrl, kTabsUrl}},

      // Typing a portion of "@ask" should give the Ask QorAI Search suggestion.
      {std::u16string(kAskQorAISearchKeyword, 0, 2), {kAskQorAISearchUrl}},
      {kAskQorAISearchKeyword, {kAskQorAISearchUrl}},
  };

  RunTest(typing_scheme_cases);
}
