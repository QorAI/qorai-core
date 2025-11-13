/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_DOWNLOAD_DOWNLOAD_UI_CONTEXT_MENU_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_DOWNLOAD_DOWNLOAD_UI_CONTEXT_MENU_H_

// Scrubs out code for histogram.
#define RecordCommandsEnabled(...)      \
  RecordCommandsEnabled(__VA_ARGS__) {} \
  void RecordCommandsEnabled_Unused(__VA_ARGS__)

#define GetMenuModel \
  UnUsed() {         \
    return nullptr;  \
  }                  \
  virtual ui::SimpleMenuModel* GetMenuModel

#include <chrome/browser/download/download_ui_context_menu.h>  // IWYU pragma: export

#undef GetMenuModel
#undef RecordCommandsEnabled

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_DOWNLOAD_DOWNLOAD_UI_CONTEXT_MENU_H_
