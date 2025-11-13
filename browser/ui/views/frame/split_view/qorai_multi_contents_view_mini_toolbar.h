/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_FRAME_SPLIT_VIEW_QORAI_MULTI_CONTENTS_VIEW_MINI_TOOLBAR_H_
#define QORAI_BROWSER_UI_VIEWS_FRAME_SPLIT_VIEW_QORAI_MULTI_CONTENTS_VIEW_MINI_TOOLBAR_H_

#include "qorai/browser/ui/color/qorai_color_id.h"
#include "chrome/browser/ui/views/frame/multi_contents_view_mini_toolbar.h"
#include "ui/base/metadata/metadata_header_macros.h"

class QoraiMultiContentsViewMiniToolbar : public MultiContentsViewMiniToolbar {
  METADATA_HEADER(QoraiMultiContentsViewMiniToolbar,
                  MultiContentsViewMiniToolbar)
 public:
  using MultiContentsViewMiniToolbar::MultiContentsViewMiniToolbar;
  ~QoraiMultiContentsViewMiniToolbar() override;

  // View:
  void OnBoundsChanged(const gfx::Rect& previous_bounds) override;

  // MultiContentsViewMiniToolbar:
  void UpdateState(bool is_active, bool is_highlighted) override;
  void OnPaint(gfx::Canvas* canvas) override;

 private:
  int GetOutlineThickness() const;
  SkPath GetPath(bool border_stroke_only) const;

  bool is_active_ = false;
  ui::ColorId stroke_color_ = kColorQoraiSplitViewInactiveWebViewBorder;
};

#endif  // QORAI_BROWSER_UI_VIEWS_FRAME_SPLIT_VIEW_QORAI_MULTI_CONTENTS_VIEW_MINI_TOOLBAR_H_
