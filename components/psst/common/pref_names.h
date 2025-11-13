// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_PSST_COMMON_PREF_NAMES_H_
#define QORAI_COMPONENTS_PSST_COMMON_PREF_NAMES_H_

#include "components/prefs/pref_service.h"

class PrefRegistrySimple;

namespace psst {

namespace prefs {
inline constexpr char kPsstEnabled[] = "qorai.psst.settings.enable_psst";
}  // namespace prefs

void RegisterProfilePrefs(PrefRegistrySimple* registry);

}  // namespace psst

#endif  // QORAI_COMPONENTS_PSST_COMMON_PREF_NAMES_H_
