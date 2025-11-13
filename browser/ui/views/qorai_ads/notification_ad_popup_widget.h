/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_ADS_NOTIFICATION_AD_POPUP_WIDGET_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_ADS_NOTIFICATION_AD_POPUP_WIDGET_H_

#include "ui/gfx/native_ui_types.h"
#include "ui/views/widget/widget.h"

namespace gfx {
class Rect;
}  // namespace gfx

namespace views {
class WidgetDelegate;
}  // namespace views

namespace ui {
class NativeTheme;
}  // namespace ui

namespace qorai_ads {

// Overrides base functionality of Widget to specify native theme used for ads
// notification popup.
class NotificationAdPopupWidget final : public views::Widget {
 public:
  NotificationAdPopupWidget();

  void InitWidget(views::WidgetDelegate* delegate,
                  const gfx::Rect& bounds,
                  gfx::NativeWindow browser_native_window,
                  gfx::NativeView browser_native_view);
};

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_ADS_NOTIFICATION_AD_POPUP_WIDGET_H_
