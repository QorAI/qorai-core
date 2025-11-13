// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SHIELDS_CORE_BROWSER_QORAI_SHIELDS_LOCALE_UTILS_H_
#define QORAI_COMPONENTS_QORAI_SHIELDS_CORE_BROWSER_QORAI_SHIELDS_LOCALE_UTILS_H_

#include <string>

class PrefService;

namespace qorai_shields {

std::string GetLanguageCodeFromLocale(const std::string& locale);

bool IsAdblockOnlyModeSupportedForLocale(const std::string& locale);

// The following function enables or disables Ad Block Only mode based on the
// locale. If the locale is not supported, it disables Ad Block Only mode and
// sets `qorai.shields.adblock_only_mode_was_enabled_for_supported_locale` pref
// value to true.
// If the locale is supported, it enables Ad Block Only mode if it was
// enabled previously for a supported locale.
void ManageAdBlockOnlyModeByLocale(PrefService* local_state,
                                   const std::string& locale);

}  // namespace qorai_shields

#endif  // QORAI_COMPONENTS_QORAI_SHIELDS_CORE_BROWSER_QORAI_SHIELDS_LOCALE_UTILS_H_
