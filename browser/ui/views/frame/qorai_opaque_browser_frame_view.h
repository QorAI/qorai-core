/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_OPAQUE_BROWSER_FRAME_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_OPAQUE_BROWSER_FRAME_VIEW_H_

#include <memory>

#include "chrome/browser/ui/views/frame/opaque_browser_frame_view.h"
#include "ui/base/metadata/metadata_header_macros.h"

class QoraiWindowFrameGraphic;

class QoraiOpaqueBrowserFrameView : public OpaqueBrowserFrameView {
  METADATA_HEADER(QoraiOpaqueBrowserFrameView, OpaqueBrowserFrameView)
 public:
  QoraiOpaqueBrowserFrameView(BrowserWidget* frame,
                              BrowserView* browser_view,
                              OpaqueBrowserFrameViewLayout* layout);
  ~QoraiOpaqueBrowserFrameView() override;

  QoraiOpaqueBrowserFrameView(const QoraiOpaqueBrowserFrameView&) = delete;
  QoraiOpaqueBrowserFrameView& operator=(
      const QoraiOpaqueBrowserFrameView&) = delete;

  // OpaqueBrowserFrameView overrides:
  void OnPaint(gfx::Canvas* canvas) override;
  int NonClientHitTest(const gfx::Point& point) override;
  void UpdateCaptionButtonPlaceholderContainerBackground() override;
  void PaintClientEdge(gfx::Canvas* canvas) const override;
  int GetTopInset(bool restored) const override;
  int GetTopAreaHeight() const override;

 private:
  bool ShouldShowVerticalTabs() const;
  std::unique_ptr<QoraiWindowFrameGraphic> frame_graphic_;
};

#endif  // QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_OPAQUE_BROWSER_FRAME_VIEW_H_
