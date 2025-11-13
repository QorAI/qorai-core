/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_TOOLBAR_BOOKMARK_BUTTON_H_
#define QORAI_BROWSER_UI_VIEWS_TOOLBAR_BOOKMARK_BUTTON_H_

#include "chrome/browser/ui/views/toolbar/toolbar_button.h"
#include "ui/base/metadata/metadata_header_macros.h"

class QoraiBookmarkButton : public ToolbarButton {
  METADATA_HEADER(QoraiBookmarkButton, ToolbarButton)
 public:
  explicit QoraiBookmarkButton(PressedCallback callback);
  QoraiBookmarkButton(const QoraiBookmarkButton&) = delete;
  QoraiBookmarkButton& operator=(const QoraiBookmarkButton&) = delete;
  ~QoraiBookmarkButton() override;

  void SetToggled(bool on);
  void UpdateImageAndText();

 private:
  bool active_ = false;
};

#endif  // QORAI_BROWSER_UI_VIEWS_TOOLBAR_BOOKMARK_BUTTON_H_
