/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_MISC_METRICS_PRIVACY_HUB_METRICS_H_
#define QORAI_COMPONENTS_MISC_METRICS_PRIVACY_HUB_METRICS_H_

#include "base/timer/wall_clock_timer.h"

#include "qorai/components/time_period_storage/monthly_storage.h"

class PrefRegistrySimple;
class PrefService;

namespace misc_metrics {

inline constexpr char kViewsMonthlyHistogramName[] = "Qorai.PrivacyHub.Views";
inline constexpr char kIsEnabledHistogramName[] = "Qorai.PrivacyHub.IsEnabled";

class PrivacyHubMetrics {
 public:
  explicit PrivacyHubMetrics(PrefService* local_state);
  ~PrivacyHubMetrics();

  PrivacyHubMetrics(const PrivacyHubMetrics&) = delete;
  PrivacyHubMetrics& operator=(const PrivacyHubMetrics&) = delete;

  static void RegisterPrefs(PrefRegistrySimple* registry);

  void RecordView();
  void RecordEnabledStatus(bool is_enabled);

 private:
  void RecordViewCount();
  void SetUpTimer();

  MonthlyStorage view_storage_;
  base::WallClockTimer report_timer_;
};

}  // namespace misc_metrics

#endif  // QORAI_COMPONENTS_MISC_METRICS_PRIVACY_HUB_METRICS_H_
