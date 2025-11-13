/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_DEVICE_CHOOSER_CONTENT_VIEW_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_DEVICE_CHOOSER_CONTENT_VIEW_H_

class Browser;

#define CreateExtraView(...)    \
  CreateExtraView(__VA_ARGS__); \
  std::unique_ptr<views::View> CreateFootnoteView(Browser* browser)

#include <chrome/browser/ui/views/device_chooser_content_view.h>  // IWYU pragma: export

#undef CreateExtraView

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_DEVICE_CHOOSER_CONTENT_VIEW_H_
