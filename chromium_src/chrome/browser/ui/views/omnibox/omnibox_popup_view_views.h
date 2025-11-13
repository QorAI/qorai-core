/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_OMNIBOX_OMNIBOX_POPUP_VIEW_VIEWS_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_OMNIBOX_OMNIBOX_POPUP_VIEW_VIEWS_H_

#include "chrome/browser/ui/omnibox/omnibox_edit_model.h"

#define OmniboxSuggestionButtonRowBrowserTest  \
  OmniboxSuggestionButtonRowBrowserTest;       \
  LocationBarView* location_bar_view() const { \
    return location_bar_view_;                 \
  }                                            \
  friend class QoraiOmniboxPopupViewViews

#define GetTargetBounds virtual GetTargetBounds

#include <chrome/browser/ui/views/omnibox/omnibox_popup_view_views.h>  // IWYU pragma: export

#undef OmniboxSuggestionButtonRowBrowserTest
#undef GetTargetBounds

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_VIEWS_OMNIBOX_OMNIBOX_POPUP_VIEW_VIEWS_H_
