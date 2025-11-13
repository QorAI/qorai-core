/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_STATS_BROWSER_QORAI_STATS_UPDATER_OBSERVER_H_
#define QORAI_COMPONENTS_QORAI_STATS_BROWSER_QORAI_STATS_UPDATER_OBSERVER_H_

#include "base/observer_list_types.h"

namespace qorai_stats {

class QoraiStatsUpdaterObserver : public base::CheckedObserver {
 public:
  ~QoraiStatsUpdaterObserver() override {}

  virtual void OnStatsPingFired() {}
};

}  // namespace qorai_stats
#endif  // QORAI_COMPONENTS_QORAI_STATS_BROWSER_QORAI_STATS_UPDATER_OBSERVER_H_
