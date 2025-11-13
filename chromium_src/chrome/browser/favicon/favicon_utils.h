// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_FAVICON_FAVICON_UTILS_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_FAVICON_FAVICON_UTILS_H_

#define ShouldThemifyFaviconForEntry                                          \
  ShouldThemifyFaviconForEntry_ChromiumImpl(content::NavigationEntry* entry); \
  bool ShouldThemifyFaviconForEntry
#include <chrome/browser/favicon/favicon_utils.h>  // IWYU pragma: export
#undef ShouldThemifyFaviconForEntry

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_FAVICON_FAVICON_UTILS_H_
