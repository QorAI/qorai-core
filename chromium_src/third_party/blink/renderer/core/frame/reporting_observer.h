/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_REPORTING_OBSERVER_H_
#define QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_REPORTING_OBSERVER_H_

#define QueueReport                   \
  QueueReport_Unused(Report* report); \
  void QueueReport

#include <third_party/blink/renderer/core/frame/reporting_observer.h>  // IWYU pragma: export

#undef QueueReport

#endif  // QORAI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_CORE_FRAME_REPORTING_OBSERVER_H_
