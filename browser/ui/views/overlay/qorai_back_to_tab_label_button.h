/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_OVERLAY_QORAI_BACK_TO_TAB_LABEL_BUTTON_H_
#define QORAI_BROWSER_UI_VIEWS_OVERLAY_QORAI_BACK_TO_TAB_LABEL_BUTTON_H_

#include "chrome/browser/ui/views/overlay/back_to_tab_label_button.h"
#include "ui/base/metadata/metadata_header_macros.h"

class QoraiBackToTabLabelButton : public BackToTabLabelButton {
  METADATA_HEADER(QoraiBackToTabLabelButton, BackToTabLabelButton)

 public:
  explicit QoraiBackToTabLabelButton(PressedCallback callback);
  ~QoraiBackToTabLabelButton() override;

  // BackToTabLabelButton:
  void OnThemeChanged() override;
};

#endif  // QORAI_BROWSER_UI_VIEWS_OVERLAY_QORAI_BACK_TO_TAB_LABEL_BUTTON_H_
