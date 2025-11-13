/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_EXTENSIONS_ICON_WITH_BADGE_IMAGE_SOURCE_H_
#define QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_EXTENSIONS_ICON_WITH_BADGE_IMAGE_SOURCE_H_

#include <optional>

namespace qorai {
class QoraiIconWithBadgeImageSource;
}

#define QORAI_ICON_WITH_BADGE_IMAGE_SOURCE_H_           \
 private:                                               \
  friend class qorai::QoraiIconWithBadgeImageSource;    \
  virtual std::optional<int> GetCustomGraphicSize();    \
  virtual std::optional<int> GetCustomGraphicXOffset(); \
  virtual std::optional<int> GetCustomGraphicYOffset(); \
                                                        \
 public:                                                \
  // #define QORAI_ICON_WITH_BADGE_IMAGE_SOURCE_H_

#define PaintBadge virtual PaintBadge
#define GetIconAreaRect virtual GetIconAreaRect
#include <chrome/browser/ui/extensions/icon_with_badge_image_source.h>  // IWYU pragma: export
#undef GetIconAreaRect
#undef PaintBadge
#undef QORAI_ICON_WITH_BADGE_IMAGE_SOURCE_H_

#endif  // QORAI_CHROMIUM_SRC_CHROME_BROWSER_UI_EXTENSIONS_ICON_WITH_BADGE_IMAGE_SOURCE_H_
