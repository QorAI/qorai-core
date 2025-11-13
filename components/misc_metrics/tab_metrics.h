/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_MISC_METRICS_TAB_METRICS_H_
#define QORAI_COMPONENTS_MISC_METRICS_TAB_METRICS_H_

#include "base/timer/wall_clock_timer.h"

#include "qorai/components/time_period_storage/weekly_storage.h"

class PrefRegistrySimple;
class PrefService;

namespace misc_metrics {

inline constexpr char kLocationNewEntriesHistogramName[] =
    "Qorai.Core.LocationNewEntries";
inline constexpr char kNewTabMethodsHistogramName[] =
    "Qorai.Core.NewTabMethods";

class TabMetrics {
 public:
  explicit TabMetrics(PrefService* local_state);
  ~TabMetrics();

  TabMetrics(const TabMetrics&) = delete;
  TabMetrics& operator=(const TabMetrics&) = delete;

  static void RegisterPrefs(PrefRegistrySimple* registry);

  void RecordLocationBarChange(bool is_new_tab);
  void RecordAppMenuNewTab();
  void RecordTabSwitcherNewTab();

 private:
  void RecordLocationEntries();
  void RecordNewTabMethods();

  void UpdateMetrics();
  void SetUpTimer();

  WeeklyStorage tab_switcher_new_tabs_storage_;
  WeeklyStorage total_new_tabs_storage_;

  WeeklyStorage new_tab_location_bar_entries_storage_;
  WeeklyStorage total_location_bar_entries_storage_;

  base::WallClockTimer report_timer_;
};

}  // namespace misc_metrics

#endif  // QORAI_COMPONENTS_MISC_METRICS_TAB_METRICS_H_
