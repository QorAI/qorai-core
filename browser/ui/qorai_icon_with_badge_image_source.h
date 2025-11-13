/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_QORAI_ICON_WITH_BADGE_IMAGE_SOURCE_H_
#define QORAI_BROWSER_UI_QORAI_ICON_WITH_BADGE_IMAGE_SOURCE_H_

#include <optional>

#include "chrome/browser/ui/extensions/icon_with_badge_image_source.h"
#include "third_party/skia/include/core/SkColor.h"

namespace gfx {
class Canvas;
class Rect;
}  // namespace gfx

namespace qorai {

inline constexpr SkColor kBadgeNotificationBG = SkColorSetRGB(0xfb, 0x54, 0x2b);
inline constexpr SkColor kBadgeTextColor = SK_ColorWHITE;

// The purpose of this subclass is to:
// - Paint the QoraiAction badge in a custom location and with a different size
//   to regular BrowserAction extensions.
class QoraiIconWithBadgeImageSource : public IconWithBadgeImageSource {
 public:
  QoraiIconWithBadgeImageSource(
      const gfx::Size& size,
      GetColorProviderCallback get_color_provider_callback,
      size_t content_image_size,
      size_t image_left_margin_extra);

  QoraiIconWithBadgeImageSource(const QoraiIconWithBadgeImageSource&) = delete;
  QoraiIconWithBadgeImageSource& operator=(
      const QoraiIconWithBadgeImageSource&) = delete;

  void SetAllowEmptyText(bool v);

  static gfx::Size GetMaxBadgeSize();

 protected:
  virtual void PaintBadgeWithoutText(const gfx::Rect& badge_rect,
                                     gfx::Canvas* canvas);

 private:
  void PaintBadge(gfx::Canvas* canvas) override;
  void PaintBadgeWithText(gfx::Canvas* canvas);

  gfx::Rect GetIconAreaRect() const override;
  gfx::Rect GetBadgeRect(size_t badge_width) const;

  std::optional<int> GetCustomGraphicSize() override;
  std::optional<int> GetCustomGraphicXOffset() override;
  std::optional<int> GetCustomGraphicYOffset() override;

  bool allow_empty_text_ = false;
  size_t content_image_size_;
  size_t image_left_margin_extra_;
};

}  // namespace qorai

#endif  // QORAI_BROWSER_UI_QORAI_ICON_WITH_BADGE_IMAGE_SOURCE_H_
