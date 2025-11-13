/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_REWARDS_CORE_PREF_REGISTRY_H_
#define QORAI_COMPONENTS_QORAI_REWARDS_CORE_PREF_REGISTRY_H_

class PrefRegistrySimple;

namespace qorai_rewards {

void RegisterProfilePrefs(PrefRegistrySimple* registry);
void RegisterProfilePrefsForMigration(PrefRegistrySimple* registry);

}  // namespace qorai_rewards

#endif  // QORAI_COMPONENTS_QORAI_REWARDS_CORE_PREF_REGISTRY_H_
