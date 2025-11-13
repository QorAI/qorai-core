/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_THIRD_PARTY_BLINK_RENDERER_MODULES_GLOBAL_PRIVACY_CONTROL_GLOBAL_PRIVACY_CONTROL_H_
#define QORAI_THIRD_PARTY_BLINK_RENDERER_MODULES_GLOBAL_PRIVACY_CONTROL_GLOBAL_PRIVACY_CONTROL_H_

#include "third_party/blink/renderer/core/execution_context/navigator_base.h"

namespace blink {

class GlobalPrivacyControl final {
 public:
  static bool globalPrivacyControl(NavigatorBase&);
};

}  // namespace blink

#endif  // QORAI_THIRD_PARTY_BLINK_RENDERER_MODULES_GLOBAL_PRIVACY_CONTROL_GLOBAL_PRIVACY_CONTROL_H_
