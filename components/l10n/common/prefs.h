/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_L10N_COMMON_PREFS_H_
#define QORAI_COMPONENTS_L10N_COMMON_PREFS_H_

class PrefRegistrySimple;
class PrefService;

namespace qorai_l10n {

void RegisterLocalStatePrefsForMigration(PrefRegistrySimple* registry);
void MigrateObsoleteLocalStatePrefs(PrefService* local_state);

}  // namespace qorai_l10n

#endif  // QORAI_COMPONENTS_L10N_COMMON_PREFS_H_
