/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_PROFILES_QORAI_AVATAR_TOOLBAR_BUTTON_H_
#define QORAI_BROWSER_UI_VIEWS_PROFILES_QORAI_AVATAR_TOOLBAR_BUTTON_H_

#include <optional>

#include "chrome/browser/ui/views/profiles/avatar_toolbar_button.h"
#include "ui/base/metadata/metadata_header_macros.h"

class BrowserView;

class QoraiAvatarToolbarButton : public AvatarToolbarButton {
  METADATA_HEADER(QoraiAvatarToolbarButton, AvatarToolbarButton)

 public:
  explicit QoraiAvatarToolbarButton(BrowserView* browser_view);
  QoraiAvatarToolbarButton(const QoraiAvatarToolbarButton&) = delete;
  QoraiAvatarToolbarButton& operator=(const QoraiAvatarToolbarButton&) = delete;
  ~QoraiAvatarToolbarButton() override;

  // ToolbarButton:
  void SetHighlight(const std::u16string& highlight_text,
                    std::optional<SkColor> highlight_color) override;
  void UpdateColorsAndInsets() override;
  void OnThemeChanged() override;
  int GetIconSize() const override;

 private:
  // AvatarToolbarButton:
  base::WeakPtrFactory<QoraiAvatarToolbarButton> weak_ptr_factory_{this};
};

#endif  // QORAI_BROWSER_UI_VIEWS_PROFILES_QORAI_AVATAR_TOOLBAR_BUTTON_H_
