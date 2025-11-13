/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "components/pref_registry/pref_registry_syncable.h"
#include "components/prefs/pref_service.h"

namespace qorai {
void RegisterBrowserStatePrefs(user_prefs::PrefRegistrySyncable* registry);
void RegisterLocalStatePrefs(PrefRegistrySimple* registry);
void MigrateObsoleteProfilePrefs(PrefService* prefs);
void MigrateObsoleteLocalStatePrefs(PrefService* prefs);
}  // namespace qorai

#define QORAI_REGISTER_BROWSER_STATE_PREFS \
  qorai::RegisterBrowserStatePrefs(registry);

#define QORAI_REGISTER_LOCAL_STATE_PREFS \
  qorai::RegisterLocalStatePrefs(registry);

#define MigrateObsoleteProfilePrefs MigrateObsoleteProfilePrefs_ChromiumImpl

#define MigrateObsoleteLocalStatePrefs \
  MigrateObsoleteLocalStatePrefs_ChromiumImpl

#include <ios/chrome/browser/shared/model/prefs/browser_prefs.mm>

#undef MigrateObsoleteLocalStatePrefs
#undef MigrateObsoleteProfilePrefs
#undef QORAI_REGISTER_LOCAL_STATE_PREFS
#undef QORAI_REGISTER_BROWSER_STATE_PREFS

void MigrateObsoleteProfilePrefs(PrefService* prefs) {
  MigrateObsoleteProfilePrefs_ChromiumImpl(prefs);
  qorai::MigrateObsoleteProfilePrefs(prefs);
}

void MigrateObsoleteLocalStatePrefs(PrefService* prefs) {
  MigrateObsoleteLocalStatePrefs_ChromiumImpl(prefs);
  qorai::MigrateObsoleteLocalStatePrefs(prefs);
}
