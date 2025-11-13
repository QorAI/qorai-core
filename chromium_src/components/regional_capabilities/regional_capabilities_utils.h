/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_REGIONAL_CAPABILITIES_REGIONAL_CAPABILITIES_UTILS_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_REGIONAL_CAPABILITIES_REGIONAL_CAPABILITIES_UTILS_H_

#include <components/regional_capabilities/regional_capabilities_utils.h>  // IWYU pragma: export

#include "qorai/components/search_engines/qorai_prepopulated_engines.h"

namespace regional_capabilities {

TemplateURLPrepopulateData::QoraiPrepopulatedEngineID GetDefaultEngine(
    country_codes::CountryId country_id,
    PrefService& prefs);

}  // namespace regional_capabilities

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_REGIONAL_CAPABILITIES_REGIONAL_CAPABILITIES_UTILS_H_
