/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_QORAI_STATS_QORAI_STATS_PREFS_H_
#define QORAI_IOS_BROWSER_QORAI_STATS_QORAI_STATS_PREFS_H_

class PrefRegistrySimple;

namespace qorai_stats {

void RegisterLocalStatePrefs(PrefRegistrySimple* registry);

}  // namespace qorai_stats

#endif  // QORAI_IOS_BROWSER_QORAI_STATS_QORAI_STATS_PREFS_H_
