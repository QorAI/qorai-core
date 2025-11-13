/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_UI_VIEWS_WIDGET_WIDGET_H_
#define QORAI_CHROMIUM_SRC_UI_VIEWS_WIDGET_WIDGET_H_

#include "build/build_config.h"

#if BUILDFLAG(IS_MAC)
#define UnlockPaintAsActive                   \
  SetWindowTitleVisibility(bool visible);     \
  void ResetWindowControlsPosition();         \
  void UpdateWindowTitleColor(SkColor color); \
  void UnlockPaintAsActive
#else
#define UnlockPaintAsActive UnlockPaintAsActive
#endif

#include <ui/views/widget/widget.h>  // IWYU pragma: export

#undef UnlockPaintAsActive

#endif  // QORAI_CHROMIUM_SRC_UI_VIEWS_WIDGET_WIDGET_H_
