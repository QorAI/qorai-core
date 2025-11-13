/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_PAGE_INFO_QORAI_SHIELDS_PAGE_INFO_VIEW_H_
#define QORAI_BROWSER_UI_VIEWS_PAGE_INFO_QORAI_SHIELDS_PAGE_INFO_VIEW_H_

#include <memory>

#include "base/functional/callback_forward.h"
#include "base/memory/raw_ptr.h"
#include "ui/base/metadata/metadata_header_macros.h"
#include "ui/views/view.h"

class BrowserWindowInterface;
class WebUIContentsWrapper;

namespace views {
class WebView;
}

// A view that displays Qorai Shields settings within the page info bubble.
class QoraiShieldsPageInfoView : public views::View {
  METADATA_HEADER(QoraiShieldsPageInfoView, views::View)

 public:
  QoraiShieldsPageInfoView(BrowserWindowInterface* browser_window_interface,
                           base::RepeatingCallback<void()> close_bubble);
  QoraiShieldsPageInfoView(const QoraiShieldsPageInfoView&) = delete;
  QoraiShieldsPageInfoView& operator=(const QoraiShieldsPageInfoView&) = delete;
  ~QoraiShieldsPageInfoView() override;

  void ShowRepeatedReloadsView();

  // views::View:
  void ChildPreferredSizeChanged(View* child) override;
  gfx::Size CalculatePreferredSize(
      const views::SizeBounds& available_size) const override;

 private:
  std::unique_ptr<WebUIContentsWrapper> CreateContentsWrapper();

  raw_ptr<BrowserWindowInterface> browser_ = nullptr;
  raw_ptr<views::WebView> web_view_ = nullptr;
  std::unique_ptr<WebUIContentsWrapper> contents_wrapper_;
};

#endif  // QORAI_BROWSER_UI_VIEWS_PAGE_INFO_QORAI_SHIELDS_PAGE_INFO_VIEW_H_
