/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_TABS_QORAI_NEW_TAB_BUTTON_H_
#define QORAI_BROWSER_UI_VIEWS_TABS_QORAI_NEW_TAB_BUTTON_H_

#include "chrome/browser/ui/views/tabs/new_tab_button.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/gfx/geometry/size.h"

class TabStrip;
namespace views {
class ButtonListener;
}

class QoraiNewTabButton : public NewTabButton {
  // Note that NewTabButton is missing METADATA_HEADER, so we need to declare
  // TabStripControlButton as paren.
  METADATA_HEADER(QoraiNewTabButton, TabStripControlButton)

 public:
  // This static members are shared with QoraiTabSearchButton
  // TODO(sko) If we could make TabSearchButton inherit QoraiNewTabButton,
  // we might not need to do this any more.
  static gfx::Size GetButtonSize();

  QoraiNewTabButton(TabStripController* tab_strip_controller,
                    PressedCallback callback,
                    const gfx::VectorIcon& icon /* this won't be used */,
                    Edge fixed_flat_edge = Edge::kNone,
                    Edge animated_flat_edge = Edge::kNone,
                    BrowserWindowInterface* browser = nullptr);
  ~QoraiNewTabButton() override;

 protected:
  // NewTabButton:
  gfx::Size CalculatePreferredSize(
      const views::SizeBounds& available_size) const override;
};

#endif  // QORAI_BROWSER_UI_VIEWS_TABS_QORAI_NEW_TAB_BUTTON_H_
