/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_ADS_NOTIFICATION_AD_BACKGROUND_PAINTER_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_ADS_NOTIFICATION_AD_BACKGROUND_PAINTER_H_

#include "ui/views/painter.h"

namespace qorai_ads {

// Background painter for notification ads with rounded corners. This draws the
// rectangle with rounded corners
class NotificationAdBackgroundPainter final : public views::Painter {
 public:
  NotificationAdBackgroundPainter(int top_radius,
                                  int bottom_radius,
                                  const SkColor color = SK_ColorWHITE);

  NotificationAdBackgroundPainter(const NotificationAdBackgroundPainter&) =
      delete;
  NotificationAdBackgroundPainter& operator=(
      const NotificationAdBackgroundPainter&) = delete;

  ~NotificationAdBackgroundPainter() override;

  // views::Painter:
  gfx::Size GetMinimumSize() const override;
  void Paint(gfx::Canvas* canvas, const gfx::Size& size) override;

 private:
  const SkScalar top_radius_;
  const SkScalar bottom_radius_;
  const SkColor color_;
};

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_ADS_NOTIFICATION_AD_BACKGROUND_PAINTER_H_
