/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_NATIVE_WIDGET_MAC_H_
#define QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_NATIVE_WIDGET_MAC_H_

#include "base/memory/weak_ptr.h"
#include "chrome/browser/ui/views/frame/browser_native_widget_mac.h"

class BrowserView;
class BrowserWidget;

class QoraiBrowserNativeWidgetMac : public BrowserNativeWidgetMac {
 public:
  QoraiBrowserNativeWidgetMac(BrowserWidget* browser_widget,
                              BrowserView* browser_view);
  ~QoraiBrowserNativeWidgetMac() override;

  // BrowserNativeWidgetMac:
  void GetWindowFrameTitlebarHeight(bool* override_titlebar_height,
                                    float* titlebar_height) override;
  void ValidateUserInterfaceItem(
      int32_t command,
      remote_cocoa::mojom::ValidateUserInterfaceItemResult* result) override;

  bool ExecuteCommand(int32_t command,
                      WindowOpenDisposition window_open_disposition,
                      bool is_before_first_responder) override;

 private:
  base::WeakPtr<BrowserView> browser_view_;
};

#endif  // QORAI_BROWSER_UI_VIEWS_FRAME_QORAI_BROWSER_NATIVE_WIDGET_MAC_H_
