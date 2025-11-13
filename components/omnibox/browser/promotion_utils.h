/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_OMNIBOX_BROWSER_PROMOTION_UTILS_H_
#define QORAI_COMPONENTS_OMNIBOX_BROWSER_PROMOTION_UTILS_H_

#include <string>

class AutocompleteInput;
class AutocompleteResult;
struct AutocompleteMatch;

namespace qorai_search_conversion {
enum class ConversionType;
}  // namespace qorai_search_conversion

// Exposed for testing.
void SortQorAISearchPromotionMatch(AutocompleteResult* result);

// True when |match| is the qorai search conversion promotion match for |input|.
bool IsQorAISearchPromotionMatch(const AutocompleteMatch& match);

qorai_search_conversion::ConversionType GetConversionTypeFromMatch(
    const AutocompleteMatch& match);
void SetConversionTypeToMatch(qorai_search_conversion::ConversionType type,
                              AutocompleteMatch* match);

#endif  // QORAI_COMPONENTS_OMNIBOX_BROWSER_PROMOTION_UTILS_H_
