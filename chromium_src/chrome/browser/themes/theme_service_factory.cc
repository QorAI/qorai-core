/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/themes/theme_service_factory.h"

#include "qorai/browser/themes/qorai_theme_service.h"

#if !BUILDFLAG(IS_LINUX)
#define QORAI_THEMESERVICEFACTORY_BUILDSERVICEINSTANCEFOR \
  using ThemeService = QoraiThemeService;
#else
// On Linux ThemeServiceAuraLinux derives from QoraiThemeService instead.
#define QORAI_THEMESERVICEFACTORY_BUILDSERVICEINSTANCEFOR
#endif

#include <chrome/browser/themes/theme_service_factory.cc>

#undef QORAI_THEMESERVICEFACTORY_BUILDSERVICEINSTANCEFOR
