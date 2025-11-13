/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_QORAI_TOOLTIPS_BOUNDS_UTIL_H_
#define QORAI_BROWSER_UI_QORAI_TOOLTIPS_BOUNDS_UTIL_H_

#include "ui/gfx/native_ui_types.h"

namespace gfx {
class Rect;
}  // namespace gfx

namespace qorai_tooltips {

void AdjustBoundsToFitWorkAreaForNativeView(gfx::Rect* bounds,
                                            gfx::NativeView native_view);

}  // namespace qorai_tooltips

#endif  // QORAI_BROWSER_UI_QORAI_TOOLTIPS_BOUNDS_UTIL_H_
