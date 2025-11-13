/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * you can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_TABS_QORAI_TAB_SEARCH_BUTTON_H_
#define QORAI_BROWSER_UI_VIEWS_TABS_QORAI_TAB_SEARCH_BUTTON_H_

#include "chrome/browser/ui/views/tabs/tab_search_button.h"
#include "third_party/skia/include/core/SkPath.h"
#include "ui/gfx/geometry/size.h"

class QoraiTabSearchButton : public TabSearchButton {
  METADATA_HEADER(QoraiTabSearchButton, TabSearchButton)
 public:
  explicit QoraiTabSearchButton(
      TabStripController* tab_strip_controller,
      BrowserWindowInterface* browser_window_interface,
      Edge fixed_flat_edge,
      Edge animated_flat_edge,
      TabStrip* tab_strip);
  ~QoraiTabSearchButton() override;
  QoraiTabSearchButton(const QoraiTabSearchButton&) = delete;
  QoraiTabSearchButton& operator=(const QoraiTabSearchButton&) = delete;

  // TabSearchButton:
  void UpdateColors() override;
  int GetCornerRadius() const override;
};

#endif  // QORAI_BROWSER_UI_VIEWS_TABS_QORAI_TAB_SEARCH_BUTTON_H_
