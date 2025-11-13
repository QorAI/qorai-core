/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_FRAME_VIEW_MAC_H_
#define QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_FRAME_VIEW_MAC_H_

#include <memory>

#include "chrome/browser/ui/views/frame/browser_frame_view_mac.h"

class QoraiWindowFrameGraphic;

class QoraiBrowserFrameViewMac : public BrowserFrameViewMac {
 public:
  QoraiBrowserFrameViewMac(BrowserWidget* browser_widget,
                           BrowserView* browser_view);
  ~QoraiBrowserFrameViewMac() override;

  QoraiBrowserFrameViewMac(const QoraiBrowserFrameViewMac&) = delete;
  QoraiBrowserFrameViewMac& operator=(const QoraiBrowserFrameViewMac&) = delete;
  gfx::Size GetMinimumSize() const override;

 private:
  bool ShouldShowWindowTitleForVerticalTabs() const;
  void UpdateWindowTitleVisibility();
  void UpdateWindowTitleAndControls();
  void UpdateWindowTitleColor();

  // BrowserFrameViewMac overrides:
  void OnPaint(gfx::Canvas* canvas) override;
  int GetTopInset(bool restored) const override;
  int NonClientHitTest(const gfx::Point& point) override;
  void OnThemeChanged() override;

  std::unique_ptr<QoraiWindowFrameGraphic> frame_graphic_;

  BooleanPrefMember show_vertical_tabs_;
  BooleanPrefMember show_title_bar_on_vertical_tabs_;
};

#endif  // QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_FRAME_VIEW_MAC_H_
