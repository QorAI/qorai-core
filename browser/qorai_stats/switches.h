// Copyright (c) 2020 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_QORAI_STATS_SWITCHES_H_
#define QORAI_BROWSER_QORAI_STATS_SWITCHES_H_

namespace qorai_stats {

namespace switches {

// Allows setting the usage server to a custom host. Useful both for manual
// testing against staging and for browser tests.
inline constexpr char kQorAIStatsUpdaterServer[] = "qorai-stats-updater-server";

}  // namespace switches
}  // namespace qorai_stats

#endif  // QORAI_BROWSER_QORAI_STATS_SWITCHES_H_
