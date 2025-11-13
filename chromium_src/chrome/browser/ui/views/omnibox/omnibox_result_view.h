/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_OMNIBOX_OMNIBOX_RESULT_VIEW_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_OMNIBOX_OMNIBOX_RESULT_VIEW_H_

#define SetMatch                       \
  UnUsed() {}                          \
  friend class QoraiOmniboxResultView; \
  virtual void SetMatch
#define OnSelectionStateChanged virtual OnSelectionStateChanged
#define GetIcon virtual GetIcon

#include <chrome/browser/ui/views/omnibox/omnibox_result_view.h>  // IWYU pragma: export

#undef GetIcon
#undef OnSelectionStateChanged
#undef SetMatch

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_OMNIBOX_OMNIBOX_RESULT_VIEW_H_
