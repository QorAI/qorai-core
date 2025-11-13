/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_PREPOPULATE_DATA_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_PREPOPULATE_DATA_H_

#include "qorai/components/search_engines/qorai_prepopulated_engines.h"

#define GetPrepopulatedFallbackSearch(...)                                   \
  GetPrepopulatedFallbackSearch(QoraiPrepopulatedEngineID default_engine_id, \
                                __VA_ARGS__)

#include <components/search_engines/template_url_prepopulate_data.h>  // IWYU pragma: export
#undef GetPrepopulatedFallbackSearch

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_PREPOPULATE_DATA_H_
