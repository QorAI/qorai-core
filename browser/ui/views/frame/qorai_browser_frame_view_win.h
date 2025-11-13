/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_FRAME_VIEW_WIN_H_
#define QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_FRAME_VIEW_WIN_H_

#include <memory>

#include "chrome/browser/ui/views/frame/browser_frame_view_win.h"
#include "components/prefs/pref_member.h"

class QoraiWindowFrameGraphic;

class QoraiBrowserFrameViewWin : public BrowserFrameViewWin {
 public:
  QoraiBrowserFrameViewWin(BrowserWidget* browser_widget,
                           BrowserView* browser_view);
  ~QoraiBrowserFrameViewWin() override;

  QoraiBrowserFrameViewWin(const QoraiBrowserFrameViewWin&) = delete;
  QoraiBrowserFrameViewWin& operator=(const QoraiBrowserFrameViewWin&) = delete;

  bool ShouldCaptionButtonsBeDrawnOverToolbar() const;

 private:
  void OnVerticalTabsPrefsChanged();

  // QoraiBrowserFrameViewWin overrides:
  void OnPaint(gfx::Canvas* canvas) override;
  int GetTopInset(bool restored) const override;
  int NonClientHitTest(const gfx::Point& point) override;
  bool ShouldShowWindowTitle(TitlebarType type) const override;
  void LayoutCaptionButtons() override;

  std::unique_ptr<QoraiWindowFrameGraphic> frame_graphic_;

  BooleanPrefMember using_vertical_tabs_;
  BooleanPrefMember showing_window_title_for_vertical_tabs_;
};

#endif  // QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_FRAME_VIEW_WIN_H_
