/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_PREFS_OBSOLETE_PREF_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_PREFS_OBSOLETE_PREF_UTIL_H_

class PrefRegistrySimple;
class PrefService;

namespace qorai_ads {

void RegisterProfilePrefsForMigration(PrefRegistrySimple* registry);
void MigrateObsoleteProfilePrefs(PrefService* prefs);

void RegisterLocalStatePrefsForMigration(PrefRegistrySimple* registry);
void MigrateObsoleteLocalStatePrefs(PrefService* local_state);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_PREFS_OBSOLETE_PREF_UTIL_H_
