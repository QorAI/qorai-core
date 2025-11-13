/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_EXTENSIONS_API_SETTINGS_PRIVATE_PREFS_UTIL_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_EXTENSIONS_API_SETTINGS_PRIVATE_PREFS_UTIL_H_

#define GetAllowlistedKeys \
  Dummy();                 \
  virtual const TypedPrefMap& GetAllowlistedKeys

#include <chrome/browser/extensions/api/settings_private/prefs_util.h>  // IWYU pragma: export
#undef GetAllowlistedKeys

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_EXTENSIONS_API_SETTINGS_PRIVATE_PREFS_UTIL_H_
