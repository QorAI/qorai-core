/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_account/prefs.h"

#include <string>

#include "qorai/components/qorai_account/features.h"
#include "qorai/components/qorai_account/pref_names.h"
#include "components/prefs/pref_registry_simple.h"

namespace qorai_account::prefs {

void RegisterPrefs(PrefRegistrySimple* registry) {
  if (features::IsQoraiAccountEnabled()) {
    registry->RegisterStringPref(kVerificationToken, std::string());
    registry->RegisterStringPref(kAuthenticationToken, std::string());
  }
}

}  // namespace qorai_account::prefs
