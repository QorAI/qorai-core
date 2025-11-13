/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_THEMES_THEME_SERVICE_AURA_LINUX_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_THEMES_THEME_SERVICE_AURA_LINUX_H_

#include "qorai/browser/themes/qorai_theme_service.h"

#undef ThemeService
#define ThemeService QoraiThemeService
#include <chrome/browser/themes/theme_service_aura_linux.h>  // IWYU pragma: export
#undef ThemeService

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_THEMES_THEME_SERVICE_AURA_LINUX_H_
