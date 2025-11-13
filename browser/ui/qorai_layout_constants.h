/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_QORAI_LAYOUT_CONSTANTS_H_
#define QORAI_BROWSER_UI_QORAI_LAYOUT_CONSTANTS_H_

#include <optional>

#include "chrome/browser/ui/layout_constants.h"

std::optional<gfx::Insets> GetQoraiLayoutInsets(LayoutInset inset);
std::optional<int> GetQoraiLayoutConstant(LayoutConstant constant);

#endif  // QORAI_BROWSER_UI_QORAI_LAYOUT_CONSTANTS_H_
