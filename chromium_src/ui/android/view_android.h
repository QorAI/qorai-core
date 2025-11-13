// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_CHROMIUM_SRC_UI_ANDROID_VIEW_ANDROID_H_
#define QORAI_CHROMIUM_SRC_UI_ANDROID_VIEW_ANDROID_H_

#define OnDragEvent                               \
  Unused() {                                      \
    return false;                                 \
  }                                               \
  friend class speedreader::SpeedreaderTabHelper; \
  bool OnDragEvent

namespace speedreader {
class SpeedreaderTabHelper;
}

#include <ui/android/view_android.h>  // IWYU pragma: export

#undef OnDragEvent

#endif  // QORAI_CHROMIUM_SRC_UI_ANDROID_VIEW_ANDROID_H_
