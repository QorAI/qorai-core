/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_origin/qorai_origin_prefs.h"

#include "qorai/components/qorai_origin/pref_names.h"
#include "components/prefs/pref_registry_simple.h"

namespace qorai_origin {

void RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
  // Register the dictionary preference that stores all QorAI policy values
  registry->RegisterDictionaryPref(kQorAIOriginPolicies);
}

}  // namespace qorai_origin
