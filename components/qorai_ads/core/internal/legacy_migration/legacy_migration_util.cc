/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/legacy_migration/legacy_migration_util.h"

#include "qorai/components/qorai_ads/core/internal/prefs/pref_util.h"
#include "qorai/components/qorai_ads/core/public/prefs/pref_names.h"

namespace qorai_ads {

bool HasMigratedState() {
  return GetProfileBooleanPref(prefs::kHasMigratedState);
}

}  // namespace qorai_ads
