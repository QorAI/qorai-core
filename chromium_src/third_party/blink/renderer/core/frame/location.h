/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_LOCATION_H_
#define QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_LOCATION_H_

#define ancestorOrigins()               \
  ancestorOrigins_ChromiumImpl() const; \
  DOMStringList* ancestorOrigins()

#include <third_party/blink/renderer/core/frame/location.h>  // IWYU pragma: export

#undef ancestorOrigins

#endif  // QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_LOCATION_H_
