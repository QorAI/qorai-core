/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_DOM_WINDOW_H_
#define QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_DOM_WINDOW_H_

#define QORAI_DOM_WINDOW_H \
 public:                   \
  LocalFrame* GetDisconnectedFrame() const;

#include <third_party/blink/renderer/core/frame/dom_window.h>  // IWYU pragma: export

#undef QORAI_DOM_WINDOW_H

#endif  // QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_DOM_WINDOW_H_
