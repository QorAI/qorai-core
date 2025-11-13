/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "components/regional_capabilities/regional_capabilities_service.h"

#include "qorai/components/search_engines/qorai_prepopulated_engines.h"

#include <components/regional_capabilities/regional_capabilities_service.cc>

namespace regional_capabilities {

TemplateURLPrepopulateData::QoraiPrepopulatedEngineID
RegionalCapabilitiesService::GetRegionalDefaultEngine() {
  return GetDefaultEngine(GetCountryIdInternal(), profile_prefs_.get());
}

}  // namespace regional_capabilities
