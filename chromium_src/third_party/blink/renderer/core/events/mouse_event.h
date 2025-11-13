/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_EVENTS_MOUSE_EVENT_H_
#define QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_EVENTS_MOUSE_EVENT_H_

#include "qorai/third_party/blink/renderer/core/farbling/qorai_session_cache.h"

#define screenX                                               \
  screenX() const {                                           \
    return qorai::FarbledPointerScreenCoordinate(             \
        view(), qorai::FarbleKey::kPointerScreenX, clientX(), \
        screenX_ChromiumImpl());                              \
  }                                                           \
  virtual double screenX_ChromiumImpl

#define screenY                                               \
  screenY() const {                                           \
    return qorai::FarbledPointerScreenCoordinate(             \
        view(), qorai::FarbleKey::kPointerScreenY, clientY(), \
        screenY_ChromiumImpl());                              \
  }                                                           \
  virtual double screenY_ChromiumImpl

#include <third_party/blink/renderer/core/events/mouse_event.h>  // IWYU pragma: export

#undef screenX
#undef screenY

#endif  // QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_EVENTS_MOUSE_EVENT_H_
