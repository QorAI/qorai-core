/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_EXECUTION_CONTEXT_NAVIGATOR_BASE_H_
#define QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_EXECUTION_CONTEXT_NAVIGATOR_BASE_H_

#include "third_party/blink/renderer/core/frame/navigator_id.h"

#define userAgent                 \
  userAgent_ChromiumImpl() const; \
  String userAgent

#include <third_party/blink/renderer/core/execution_context/navigator_base.h>  // IWYU pragma: export

#undef userAgent

#endif  // QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_EXECUTION_CONTEXT_NAVIGATOR_BASE_H_
