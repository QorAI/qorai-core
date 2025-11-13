/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/omnibox/browser/qorai_bookmark_provider.h"

#include <memory>
#include <string_view>

#include "base/memory/scoped_refptr.h"
#include "base/strings/utf_string_conversions.h"
#include "base/test/task_environment.h"
#include "qorai/components/omnibox/browser/qorai_fake_autocomplete_provider_client.h"
#include "qorai/components/omnibox/browser/qorai_omnibox_prefs.h"
#include "components/bookmarks/browser/bookmark_model.h"
#include "components/bookmarks/test/test_bookmark_client.h"
#include "components/omnibox/browser/autocomplete_input.h"
#include "components/omnibox/browser/test_scheme_classifier.h"
#include "components/prefs/pref_service.h"
#include "components/search_engines/search_engines_test_environment.h"
#include "components/search_engines/template_url_service.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

class QorAIBookmarkProviderTest : public testing::Test {
 public:
  QorAIBookmarkProviderTest()
      : model_(bookmarks::TestBookmarkClient::CreateModel()) {}

  AutocompleteInput CreateAutocompleteInput(std::string_view text) {
    AutocompleteInput input(base::UTF8ToUTF16(text),
                            metrics::OmniboxEventProto::OTHER, classifier_);
    return input;
  }

  void SetUp() override {
    EXPECT_CALL(client_, GetBookmarkModel())
        .WillRepeatedly(testing::Return(model_.get()));
    EXPECT_CALL(client_, GetSchemeClassifier())
        .WillRepeatedly(testing::ReturnRef(classifier_));
    auto* node = client_.GetBookmarkModel()->other_node();
    client_.GetBookmarkModel()->AddURL(node, 0, u"Hello",
                                       GURL("https://example.com"));
    client_.set_template_url_service(
        search_engines_test_environment_.template_url_service());
    provider_ = base::MakeRefCounted<QorAIBookmarkProvider>(&client_);
  }

  PrefService* prefs() { return client_.GetPrefs(); }

 protected:
  base::test::SingleThreadTaskEnvironment task_environment_;
  TestSchemeClassifier classifier_;
  search_engines::SearchEnginesTestEnvironment search_engines_test_environment_;
  QorAIFakeAutocompleteProviderClient client_;
  std::unique_ptr<bookmarks::BookmarkModel> model_;
  scoped_refptr<QorAIBookmarkProvider> provider_;
};

TEST_F(QorAIBookmarkProviderTest, SuggestionsDisabledNoResults) {
  prefs()->SetBoolean(omnibox::kBookmarkSuggestionsEnabled, false);
  provider_->Start(CreateAutocompleteInput("Hello"), true);
  EXPECT_TRUE(provider_->matches().empty());
}

TEST_F(QorAIBookmarkProviderTest, SuggestionsEnabledHasResults) {
  prefs()->SetBoolean(omnibox::kBookmarkSuggestionsEnabled, true);
  provider_->Start(CreateAutocompleteInput("Hello"), true);
  EXPECT_FALSE(provider_->matches().empty());
}

TEST_F(QorAIBookmarkProviderTest, TitleContainsQueryCanBeDefaultMatch) {
  prefs()->SetBoolean(omnibox::kBookmarkSuggestionsEnabled, true);
  provider_->Start(CreateAutocompleteInput("Hello"), true);
  EXPECT_FALSE(provider_->matches().empty());
  EXPECT_TRUE(provider_->matches()[0].allowed_to_be_default_match);
}

TEST_F(QorAIBookmarkProviderTest, URLContainsQueryCanBeDefaultMatch) {
  prefs()->SetBoolean(omnibox::kBookmarkSuggestionsEnabled, true);
  provider_->Start(CreateAutocompleteInput("example"), true);
  EXPECT_FALSE(provider_->matches().empty());
  EXPECT_TRUE(provider_->matches()[0].allowed_to_be_default_match);
}

TEST_F(QorAIBookmarkProviderTest, ContainsIsCaseInsensitive) {
  prefs()->SetBoolean(omnibox::kBookmarkSuggestionsEnabled, true);
  provider_->Start(CreateAutocompleteInput("EXAMPLE"), true);
  EXPECT_FALSE(provider_->matches().empty());
  EXPECT_TRUE(provider_->matches()[0].allowed_to_be_default_match);

  provider_->Start(CreateAutocompleteInput("HELLO"), true);
  EXPECT_FALSE(provider_->matches().empty());
  EXPECT_TRUE(provider_->matches()[0].allowed_to_be_default_match);
}

TEST_F(QorAIBookmarkProviderTest, QueryIsNotExactCannotBeDefaultMatch) {
  prefs()->SetBoolean(omnibox::kBookmarkSuggestionsEnabled, true);
  provider_->Start(CreateAutocompleteInput("Hello example"), true);
  EXPECT_FALSE(provider_->matches().empty());
  EXPECT_FALSE(provider_->matches()[0].allowed_to_be_default_match);
}

TEST_F(QorAIBookmarkProviderTest, DontBumpContainsQueryIfKeywordIsUsed) {
  prefs()->SetBoolean(omnibox::kBookmarkSuggestionsEnabled, true);
  auto input = CreateAutocompleteInput("Hello");
  input.set_keyword_mode_entry_method(
      metrics::OmniboxEventProto::KeywordModeEntryMethod::
          OmniboxEventProto_KeywordModeEntryMethod_KEYBOARD_SHORTCUT);
  input.set_prefer_keyword(true);
  input.set_allow_exact_keyword_match(true);
  provider_->Start(input, true);

  EXPECT_FALSE(provider_->matches().empty());
  EXPECT_FALSE(provider_->matches()[0].allowed_to_be_default_match);
}

TEST_F(QorAIBookmarkProviderTest, ContainsQueryBumpsRelevance) {
  prefs()->SetBoolean(omnibox::kBookmarkSuggestionsEnabled, true);
  provider_->Start(CreateAutocompleteInput("Hello"), true);
  EXPECT_FALSE(provider_->matches().empty());
  EXPECT_TRUE(provider_->matches()[0].allowed_to_be_default_match);
  // Note: 1199 is the max relevance score for a bookmark upstream.
  EXPECT_GT(provider_->matches()[0].relevance, 1199);
}

TEST_F(QorAIBookmarkProviderTest, TitleOnlyMatchSetsURL) {
  prefs()->SetBoolean(omnibox::kBookmarkSuggestionsEnabled, true);
  provider_->Start(CreateAutocompleteInput("Hello"), true);
  EXPECT_EQ(provider_->matches().size(), 1u);
  EXPECT_TRUE(provider_->matches()[0].allowed_to_be_default_match);
  EXPECT_EQ(provider_->matches()[0].contents, u"example.com");
}
