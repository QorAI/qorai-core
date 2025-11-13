/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

// Brand-specific types and constants for Google Chrome.

#ifndef QORAI_CHROMIUM_SRC_CHROME_INSTALL_STATIC_INSTALL_CONSTANTS_H_
#define QORAI_CHROMIUM_SRC_CHROME_INSTALL_STATIC_INSTALL_CONSTANTS_H_

#if defined(OFFICIAL_BUILD)
// clang-format off
// NOLINTBEGIN(sort-order)
#include "chrome/install_static/buildflags.h"
#include "chrome/install_static/qorai_stash_google_update_integration.h"
#define BUILDFLAG_INTERNAL_USE_GOOGLE_UPDATE_INTEGRATION() (1)
// NOLINTEND(sort-order)
// clang-format on
#endif  // defined(OFFICIAL_BUILD)

#include <chrome/install_static/install_constants.h>  // IWYU pragma: export

#if defined(OFFICIAL_BUILD)
#include "chrome/install_static/qorai_restore_google_update_integration.h"
#endif

#endif  // QORAI_CHROMIUM_SRC_CHROME_INSTALL_STATIC_INSTALL_CONSTANTS_H_
