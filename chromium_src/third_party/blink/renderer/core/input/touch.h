/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_INPUT_TOUCH_H_
#define QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_INPUT_TOUCH_H_

#include "qorai/third_party/blink/renderer/core/farbling/qorai_session_cache.h"

#define screenX                                                                \
  screenX() const {                                                            \
    return qorai::FarbledPointerScreenCoordinate(                              \
        target()->ToDOMWindow(), qorai::FarbleKey::kPointerScreenX, clientX(), \
        screenX_ChromiumImpl());                                               \
  }                                                                            \
  double screenX_ChromiumImpl

#define screenY                                                                \
  screenY() const {                                                            \
    return qorai::FarbledPointerScreenCoordinate(                              \
        target()->ToDOMWindow(), qorai::FarbleKey::kPointerScreenY, clientY(), \
        screenY_ChromiumImpl());                                               \
  }                                                                            \
  double screenY_ChromiumImpl

#include <third_party/blink/renderer/core/input/touch.h>  // IWYU pragma: export

#undef screenX
#undef screenY

#endif  // QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_INPUT_TOUCH_H_
