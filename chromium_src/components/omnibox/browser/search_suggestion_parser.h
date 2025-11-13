/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_OMNIBOX_BROWSER_SEARCH_SUGGESTION_PARSER_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_OMNIBOX_BROWSER_SEARCH_SUGGESTION_PARSER_H_

#define ParseSuggestResults                                                   \
  ParseSuggestResults(                                                        \
      const base::Value::List& root_list, const AutocompleteInput& input,     \
      const AutocompleteSchemeClassifier& scheme_classifier,                  \
      int default_result_relevance, bool is_keyword_result, Results* results, \
      bool is_qorai_rich_suggestion = false);                                 \
  static bool ParseSuggestResults_Chromium

#include <components/omnibox/browser/search_suggestion_parser.h>  // IWYU pragma: export

#undef ParseSuggestResults

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_OMNIBOX_BROWSER_SEARCH_SUGGESTION_PARSER_H_
