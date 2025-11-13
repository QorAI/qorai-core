/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_SEARCH_CONVERSION_CONSTANTS_H_
#define QORAI_COMPONENTS_QORAI_SEARCH_CONVERSION_CONSTANTS_H_

namespace qorai_search_conversion {

inline constexpr char kQoraiSearchConversionPromotionURL[] =
    "https://search.qorai.com/search?q={SearchTerms}&action=makeDefault";
inline constexpr char kSearchTermsParameter[] = "{SearchTerms}";

}  // namespace qorai_search_conversion

#endif  // QORAI_COMPONENTS_QORAI_SEARCH_CONVERSION_CONSTANTS_H_
