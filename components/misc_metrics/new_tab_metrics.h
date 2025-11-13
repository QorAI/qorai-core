// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_MISC_METRICS_NEW_TAB_METRICS_H_
#define QORAI_COMPONENTS_MISC_METRICS_NEW_TAB_METRICS_H_

#include "base/timer/wall_clock_timer.h"
#include "qorai/components/qorai_new_tab_ui/qorai_new_tab_page.mojom.h"
#include "qorai/components/time_period_storage/weekly_storage.h"
#include "mojo/public/cpp/bindings/receiver_set.h"

class PrefRegistrySimple;
class PrefService;

namespace misc_metrics {

inline constexpr char kNTPSearchEngineHistogramName[] =
    "Qorai.Search.WidgetDefault";
inline constexpr char kNTPSearchUsageHistogramName[] =
    "Qorai.Search.WidgetUsage";
inline constexpr char kNTPGoogleWidgetUsageHistogramName[] =
    "Qorai.Search.GoogleWidgetUsage";

class NewTabMetrics : public qorai_new_tab_page::mojom::NewTabMetrics {
 public:
  explicit NewTabMetrics(PrefService* local_state);
  ~NewTabMetrics() override;

  NewTabMetrics(const NewTabMetrics&) = delete;
  NewTabMetrics& operator=(const NewTabMetrics&) = delete;

  static void RegisterPrefs(PrefRegistrySimple* registry);

  void Bind(
      mojo::PendingReceiver<qorai_new_tab_page::mojom::NewTabMetrics> receiver);

  // qorai_new_tab_page::mojom::NewTabMetrics:
  void ReportNTPSearchDefaultEngine(
      std::optional<int64_t> prepopulate_id) override;
  void ReportNTPSearchUsage(int64_t prepopulate_id) override;

 private:
  void ReportCounts();

  mojo::ReceiverSet<qorai_new_tab_page::mojom::NewTabMetrics> receivers_;

  WeeklyStorage usage_storage_;

  base::WallClockTimer update_timer_;
};

}  // namespace misc_metrics

#endif  // QORAI_COMPONENTS_MISC_METRICS_NEW_TAB_METRICS_H_
