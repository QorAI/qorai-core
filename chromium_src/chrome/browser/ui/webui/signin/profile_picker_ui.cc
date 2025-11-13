/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/ui/webui/signin/profile_picker_ui.h"

#include "qorai/grit/qorai_generated_resources.h"
#include "chrome/browser/signin/account_consistency_mode_manager.h"
#include "chrome/grit/generated_resources.h"

namespace {

class QoraiAccountConsistencyModeManager {
 public:
  static bool IsDiceSignInAllowed() { return false; }
};

}  // namespace

#define AccountConsistencyModeManager QoraiAccountConsistencyModeManager
#include <chrome/browser/ui/webui/signin/profile_picker_ui.cc>
#undef AccountConsistencyModeManager
