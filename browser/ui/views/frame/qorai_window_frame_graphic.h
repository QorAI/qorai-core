/* Copyright 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_WINDOW_FRAME_GRAPHIC_H_
#define QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_WINDOW_FRAME_GRAPHIC_H_

namespace gfx {
class Canvas;
class Rect;
}  // namespace gfx

namespace content {
class BrowserContext;
}  // namespace content

class QoraiWindowFrameGraphic {
 public:
  explicit QoraiWindowFrameGraphic(content::BrowserContext* context);
  virtual ~QoraiWindowFrameGraphic();

  QoraiWindowFrameGraphic(const QoraiWindowFrameGraphic&) = delete;
  QoraiWindowFrameGraphic& operator=(const QoraiWindowFrameGraphic&) = delete;

  void Paint(gfx::Canvas* canvas, const gfx::Rect& frame_bounds);

 private:
  const bool is_tor_window_;
};

#endif  // QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_WINDOW_FRAME_GRAPHIC_H_
