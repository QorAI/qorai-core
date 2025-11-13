/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_SEARCH_ENGINE_SEARCH_ENGINE_SUBDOMAIN_CONSTANTS_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_SEARCH_ENGINE_SEARCH_ENGINE_SUBDOMAIN_CONSTANTS_H_

#include <string_view>

#include "base/containers/fixed_flat_set.h"
#include "base/containers/flat_tree.h"

namespace qorai_ads {

// See https://www.wikipedia.org/.
inline constexpr auto kWikipediaSearchEngineSubdomains =
    base::MakeFixedFlatSet<std::string_view>(
        base::sorted_unique,
        {"af", "ar", "arz", "ast", "az",  "azb", "be", "bg",    "bn",
         "ca", "ce", "ceb", "cs",  "cy",  "da",  "de", "el",    "en",
         "eo", "es", "et",  "eu",  "fa",  "fi",  "fr", "gl",    "he",
         "hi", "hr", "hu",  "hy",  "id",  "it",  "ja", "ka",    "kk",
         "ko", "la", "lt",  "lv",  "min", "mk",  "ms", "my",    "nan",
         "nl", "nn", "no",  "pl",  "pt",  "ro",  "ru", "sh",    "simple",
         "sk", "sl", "sr",  "sv",  "ta",  "tg",  "th", "tr",    "tt",
         "uk", "ur", "uz",  "vi",  "vo",  "war", "zh", "zh-yue"});

// See https://uk.yahoo.com/everything/world.
inline constexpr auto kYahooSearchEngineSubdomains =
    base::MakeFixedFlatSet<std::string_view>(
        base::sorted_unique,
        {"au",      "be", "br",       "ca", "de", "en-maktoob", "es",
         "espanol", "fr", "fr-be",    "gr", "hk", "id",         "ie",
         "in",      "it", "malaysia", "nz", "ph", "qc",         "ro",
         "se",      "sg", "tw",       "uk", "vn", "www",        "za"});

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_SEARCH_ENGINE_SEARCH_ENGINE_SUBDOMAIN_CONSTANTS_H_
