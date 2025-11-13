/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SPEEDREADER_SPEEDREADER_PREF_MIGRATION_H_
#define QORAI_COMPONENTS_SPEEDREADER_SPEEDREADER_PREF_MIGRATION_H_

class PrefService;

class PrefRegistrySimple;

namespace speedreader {

void RegisterProfilePrefsForMigration(PrefRegistrySimple* registry);
void MigrateObsoleteProfilePrefs(PrefService* prefs);

}  // namespace speedreader

#endif  // QORAI_COMPONENTS_SPEEDREADER_SPEEDREADER_PREF_MIGRATION_H_
