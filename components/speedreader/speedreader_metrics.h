/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SPEEDREADER_SPEEDREADER_METRICS_H_
#define QORAI_COMPONENTS_SPEEDREADER_SPEEDREADER_METRICS_H_

#include "base/timer/wall_clock_timer.h"
#include "qorai/components/time_period_storage/monthly_storage.h"

class PrefRegistrySimple;
class PrefService;
class HostContentSettingsMap;

namespace speedreader {

inline constexpr char kSpeedreaderPageViewsHistogramName[] =
    "QorAI.Speedreader.PageViews";
inline constexpr char kSpeedreaderEnabledSitesHistogramName[] =
    "QorAI.Speedreader.EnabledSites";

class SpeedreaderMetrics {
 public:
  SpeedreaderMetrics(PrefService* local_state,
                     HostContentSettingsMap* host_content_settings_map,
                     bool is_allowed_for_all_readable_sites);
  ~SpeedreaderMetrics();

  SpeedreaderMetrics(const SpeedreaderMetrics&) = delete;
  SpeedreaderMetrics& operator=(const SpeedreaderMetrics&) = delete;

  static void RegisterPrefs(PrefRegistrySimple* registry);

  void RecordPageView();

  void UpdateEnabledSitesMetric(bool is_allowed_for_all_readable_sites);

 private:
  void ReportPageViews();

  MonthlyStorage page_views_storage_;
  raw_ptr<HostContentSettingsMap> host_content_settings_map_;
  raw_ptr<PrefService> local_state_;

  base::WallClockTimer update_timer_;
};

}  // namespace speedreader

#endif  // QORAI_COMPONENTS_SPEEDREADER_SPEEDREADER_METRICS_H_
