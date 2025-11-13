/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_REGIONAL_CAPABILITIES_REGIONAL_CAPABILITIES_SERVICE_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_REGIONAL_CAPABILITIES_REGIONAL_CAPABILITIES_SERVICE_H_

#include "qorai/components/search_engines/qorai_prepopulated_engines.h"

#define GetRegionalPrepopulatedEngines \
  GetRegionalPrepopulatedEngines();    \
  TemplateURLPrepopulateData::QoraiPrepopulatedEngineID GetRegionalDefaultEngine

#include <components/regional_capabilities/regional_capabilities_service.h>  // IWYU pragma: export
#undef GetRegionalPrepopulatedEngines

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_REGIONAL_CAPABILITIES_REGIONAL_CAPABILITIES_SERVICE_H_
