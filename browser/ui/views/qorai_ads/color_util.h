/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_QORAI_ADS_COLOR_UTIL_H_
#define QORAI_BROWSER_UI_VIEWS_QORAI_ADS_COLOR_UTIL_H_

#include <string_view>

#include "third_party/skia/include/core/SkColor.h"

namespace qorai_ads {

// Converts a string of the form "RRGGBB" to a `SkColor`.
bool RgbStringToSkColor(std::string_view rgb, SkColor* color);

}  // namespace qorai_ads

#endif  // QORAI_BROWSER_UI_VIEWS_QORAI_ADS_COLOR_UTIL_H_
