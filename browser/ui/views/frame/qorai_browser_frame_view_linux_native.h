/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_FRAME_VIEW_LINUX_NATIVE_H_
#define QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_FRAME_VIEW_LINUX_NATIVE_H_

#include <memory>
#include <utility>

#include "chrome/browser/ui/views/frame/browser_frame_view_linux_native.h"

class QoraiBrowserFrameViewLinuxNative : public BrowserFrameViewLinuxNative {
  METADATA_HEADER(QoraiBrowserFrameViewLinuxNative, BrowserFrameViewLinuxNative)
 public:
  QoraiBrowserFrameViewLinuxNative(
      BrowserWidget* frame,
      BrowserView* browser_view,
      BrowserFrameViewLayoutLinuxNative* layout,
      std::unique_ptr<ui::NavButtonProvider> nav_button_provider);
  ~QoraiBrowserFrameViewLinuxNative() override;

  // Returns caption buttons width provided by GTK.
  std::pair<int, int> leading_trailing_caption_button_width() const {
    return leading_trailing_caption_button_width_;
  }

  // BrowserFrameViewLinuxNative:
  void MaybeUpdateCachedFrameButtonImages() override;
  void Layout(PassKey) override;

 private:
  views::Button* FrameButtonToButton(views::FrameButton frame_button);

  void UpdateLeadingTrailingCaptionButtonWidth();

  std::pair<int, int> leading_trailing_caption_button_width_;
};

#endif  // QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_FRAME_VIEW_LINUX_NATIVE_H_
