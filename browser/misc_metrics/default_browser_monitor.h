/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_MISC_METRICS_DEFAULT_BROWSER_MONITOR_H_
#define QORAI_BROWSER_MISC_METRICS_DEFAULT_BROWSER_MONITOR_H_

#include "base/memory/weak_ptr.h"
#include "base/task/sequenced_task_runner.h"
#include "base/timer/wall_clock_timer.h"

class PrefService;

namespace misc_metrics {

inline constexpr char kDefaultBrowserHistogramName[] = "Qorai.Core.IsDefault";
inline constexpr char kDefaultBrowserDailyHistogramName[] =
    "Qorai.Core.IsDefaultDaily";

// Periodically checks if the browser is the default browser and reports the
// relevant metrics via P3A.
class DefaultBrowserMonitor {
 public:
  explicit DefaultBrowserMonitor(PrefService* local_state);
  ~DefaultBrowserMonitor();

  DefaultBrowserMonitor(const DefaultBrowserMonitor&) = delete;
  DefaultBrowserMonitor& operator=(const DefaultBrowserMonitor&) = delete;

  void SetGetDefaultBrowserCallbackForTesting(
      base::RepeatingCallback<bool()> callback);
  void Start();

 private:
  void CheckDefaultBrowserState();
  void OnDefaultBrowserStateReceived(bool is_default);

  raw_ptr<PrefService> local_state_;
  scoped_refptr<base::SequencedTaskRunner> task_runner_;
  base::WallClockTimer timer_;
  base::RepeatingCallback<bool()> get_default_browser_callback_;

  base::WeakPtrFactory<DefaultBrowserMonitor> weak_factory_{this};
};

}  // namespace misc_metrics

#endif  // QORAI_BROWSER_MISC_METRICS_DEFAULT_BROWSER_MONITOR_H_
