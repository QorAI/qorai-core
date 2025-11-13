/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_HISTORY_CORE_BROWSER_TOP_SITES_CONSTANTS_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_HISTORY_CORE_BROWSER_TOP_SITES_CONSTANTS_H_

// Needs 12 items for our NTP top site tiles.
#define kTopSitesNumber \
  kTopSitesNumber = 12; \
  static constexpr size_t kTopSitesNumber_Unused

#include <components/history/core/browser/top_sites_constants.h>  // IWYU pragma: export

#undef kTopSitesNumber

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_HISTORY_CORE_BROWSER_TOP_SITES_CONSTANTS_H_
