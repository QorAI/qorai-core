/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_WEBUI_SETTINGS_SITE_SETTINGS_HANDLER_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_WEBUI_SETTINGS_SITE_SETTINGS_HANDLER_H_

#define SiteSettingsHandlerBaseTest \
  SiteSettingsHandlerBaseTest;      \
  friend class QoraiSiteSettingsHandler
#define RemoveNonModelData virtual RemoveNonModelData

#include <chrome/browser/ui/webui/settings/site_settings_handler.h>  // IWYU pragma: export

#undef SiteSettingsHandlerBaseTest
#undef RemoveNonModelData

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_WEBUI_SETTINGS_SITE_SETTINGS_HANDLER_H_
