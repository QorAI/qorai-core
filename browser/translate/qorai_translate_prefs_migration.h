/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_TRANSLATE_QORAI_TRANSLATE_PREFS_MIGRATION_H_
#define QORAI_BROWSER_TRANSLATE_QORAI_TRANSLATE_PREFS_MIGRATION_H_

class PrefRegistrySimple;
class PrefService;

namespace translate {

namespace prefs {
inline constexpr char kMigratedToInternalTranslation[] =
    "qorai.translate_migrated_from_extension";
}  // namespace prefs

void RegisterQoraiProfilePrefsForMigration(PrefRegistrySimple* registry);

void ClearMigrationQoraiProfilePrefs(PrefService* prefs);

}  // namespace translate

#endif  // QORAI_BROWSER_TRANSLATE_QORAI_TRANSLATE_PREFS_MIGRATION_H_
