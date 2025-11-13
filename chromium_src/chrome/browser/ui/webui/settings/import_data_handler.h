/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_WEBUI_SETTINGS_IMPORT_DATA_HANDLER_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_WEBUI_SETTINGS_IMPORT_DATA_HANDLER_H_

#define QORAI_IMPORT_DATA_HANDLER_H \
 private: \
  friend class QoraiImportDataHandler;

#define StartImport virtual StartImport

#include <chrome/browser/ui/webui/settings/import_data_handler.h>  // IWYU pragma: export

#undef QORAI_IMPORT_DATA_HANDLER_H
#undef StartImport

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_WEBUI_SETTINGS_IMPORT_DATA_HANDLER_H_
