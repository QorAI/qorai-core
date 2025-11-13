/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_OMNIBOX_OMNIBOX_ROW_VIEW_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_OMNIBOX_OMNIBOX_ROW_VIEW_H_

#include "ui/views/view.h"

#define GetInsets           \
  GetInsets_UnUsed() const; \
  gfx::Insets GetInsets

#include <chrome/browser/ui/views/omnibox/omnibox_row_view.h>  // IWYU pragma: export

#undef GetInsets

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_OMNIBOX_OMNIBOX_ROW_VIEW_H_
