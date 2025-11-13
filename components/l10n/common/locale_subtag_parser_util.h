/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_L10N_COMMON_LOCALE_SUBTAG_PARSER_UTIL_H_
#define QORAI_COMPONENTS_L10N_COMMON_LOCALE_SUBTAG_PARSER_UTIL_H_

#include <string>

namespace qorai_l10n {

struct LocaleSubtagInfo;

// Parses the given |locale| and returns |LocaleSubtagInfo|.
LocaleSubtagInfo ParseLocaleSubtags(std::string_view locale);

}  // namespace qorai_l10n

#endif  // QORAI_COMPONENTS_L10N_COMMON_LOCALE_SUBTAG_PARSER_UTIL_H_
