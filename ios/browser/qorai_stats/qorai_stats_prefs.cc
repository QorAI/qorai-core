/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/ios/browser/qorai_stats/qorai_stats_prefs.h"

#include "base/time/time.h"
#include "qorai/components/qorai_wallet/browser/pref_names.h"
#include "qorai/components/constants/pref_names.h"
#include "components/prefs/pref_registry_simple.h"

namespace qorai_stats {

void RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
  registry->RegisterBooleanPref(kStatsReportingEnabled, true);
  registry->RegisterTimePref(kQoraiWalletPingReportedUnlockTime, base::Time());
}

}  // namespace qorai_stats
