/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_OMNIBOX_QORAI_OMNIBOX_POPUP_VIEW_VIEWS_H_
#define QORAI_BROWSER_UI_VIEWS_OMNIBOX_QORAI_OMNIBOX_POPUP_VIEW_VIEWS_H_

#include "chrome/browser/ui/views/omnibox/omnibox_popup_view_views.h"

class QoraiOmniboxPopupViewViews : public OmniboxPopupViewViews {
  METADATA_HEADER(QoraiOmniboxPopupViewViews, OmniboxPopupViewViews)
 public:

  using OmniboxPopupViewViews::OmniboxPopupViewViews;
  ~QoraiOmniboxPopupViewViews() override;

  int GetLocationBarViewWidth() const;

  // OmniboxPopupViewViews:
  gfx::Rect GetTargetBounds() const override;
};

#endif  // QORAI_BROWSER_UI_VIEWS_OMNIBOX_QORAI_OMNIBOX_POPUP_VIEW_VIEWS_H_
