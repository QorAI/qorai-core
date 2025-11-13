/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_ADS_BOUNDS_UTIL_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_ADS_BOUNDS_UTIL_H_

#include "ui/gfx/native_ui_types.h"

namespace gfx {
class Rect;
}  // namespace gfx

namespace display {
class Display;
}  // namespace display

namespace views {
class Widget;
}  // namespace views

namespace qorai_ads {

gfx::Rect GetDefaultDisplayScreenWorkArea(gfx::NativeView browser_native_view);

void AdjustBoundsAndSnapToFitWorkAreaForNativeView(const views::Widget& widget,
                                                   gfx::Rect* bounds);

// Exposed here to be available in tests.
void SnapBoundsToEdgeOfWorkArea(const gfx::Rect& work_area, gfx::Rect* bounds);

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_ADS_BOUNDS_UTIL_H_
