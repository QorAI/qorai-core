/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_origin/pref_names.h"

#include "components/prefs/pref_registry_simple.h"

namespace qorai_origin::prefs {

void RegisterProfilePrefs(PrefRegistrySimple* registry) {
#if BUILDFLAG(IS_ANDROID)
  registry->RegisterBooleanPref(kQorAIOriginSubscriptionActiveAndroid, false);
  registry->RegisterStringPref(kQorAIOriginPurchaseTokenAndroid, "");
  registry->RegisterStringPref(kQorAIOriginPackageNameAndroid, "");
  registry->RegisterStringPref(kQorAIOriginProductIdAndroid, "");
  registry->RegisterStringPref(kQorAIOriginOrderIdAndroid, "");
  // 0 is not linked
  registry->RegisterIntegerPref(kQorAIOriginSubscriptionLinkStatusAndroid, 0);
#endif
}

}  // namespace qorai_origin::prefs
