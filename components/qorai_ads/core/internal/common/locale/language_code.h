/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_LOCALE_LANGUAGE_CODE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_LOCALE_LANGUAGE_CODE_H_

#include <optional>
#include <string>

namespace qorai_ads {

// Return the current language of the device as string.
std::optional<std::string> MaybeGetLanguageCodeString();

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_LOCALE_LANGUAGE_CODE_H_
