/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_SYSTEM_MENU_MODEL_BUILDER_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_SYSTEM_MENU_MODEL_BUILDER_H_

#include "chrome/browser/ui/views/frame/system_menu_model_delegate.h"

#define Init                                \
  UnUsed();                                 \
                                            \
 private:                                   \
  friend class QoraiSystemMenuModelBuilder; \
                                            \
 public:                                    \
  void Init

#define BuildSystemMenuForBrowserWindow virtual BuildSystemMenuForBrowserWindow

#include <chrome/browser/ui/views/frame/system_menu_model_builder.h>  // IWYU pragma: export

#undef BuildSystemMenuForBrowserWindow
#undef Init

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_FRAME_SYSTEM_MENU_MODEL_BUILDER_H_
