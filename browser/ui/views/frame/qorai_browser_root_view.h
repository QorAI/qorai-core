/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_ROOT_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_ROOT_VIEW_H_

#include "base/scoped_observation.h"
#include "chrome/browser/ui/views/frame/browser_root_view.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/native_theme/native_theme.h"

class Browser;

// Observe native theme changes to propagate qorai theme change notification
// to child views for non-normal profile windows.
// W/o this, OnThemeChanged() is not called for private/tor window
// whenever qorai theme is changed because these window uses dark theme
// provider always.
class QoraiBrowserRootView : public BrowserRootView,
                             public ui::NativeThemeObserver {
  METADATA_HEADER(QoraiBrowserRootView, BrowserRootView)
 public:
  QoraiBrowserRootView(BrowserView* browser_view, views::Widget* widget);
  ~QoraiBrowserRootView() override;

  // BrowserRootView:
  bool OnMouseWheel(const ui::MouseWheelEvent& event) override;

  // ui::NativeThemeObserver overrides:
  void OnNativeThemeUpdated(ui::NativeTheme* observed_theme) override;

 private:
  raw_ptr<Browser, DanglingUntriaged> browser_ = nullptr;
  base::ScopedObservation<ui::NativeTheme, ui::NativeThemeObserver>
      theme_observation_{this};
};

#endif  // QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_ROOT_VIEW_H_
