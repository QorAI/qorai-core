/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_VPN_BROWSER_QORAI_VPN_METRICS_H_
#define QORAI_COMPONENTS_QORAI_VPN_BROWSER_QORAI_VPN_METRICS_H_

#include "base/memory/weak_ptr.h"
#include "base/timer/wall_clock_timer.h"
#include "qorai/components/misc_metrics/uptime_monitor.h"
#include "qorai/components/time_period_storage/weekly_storage.h"
#include "build/build_config.h"
#include "components/prefs/pref_change_registrar.h"

class PrefService;

namespace qorai_vpn {

inline constexpr char kNewUserReturningHistogramName[] =
    "Qorai.VPN.NewUserReturning";
inline constexpr char kDaysInMonthUsedHistogramName[] =
    "Qorai.VPN.DaysInMonthUsed";
inline constexpr char kLastUsageTimeHistogramName[] = "Qorai.VPN.LastUsageTime";
inline constexpr char kWidgetUsageHistogramName[] = "Qorai.VPN.WidgetUsage";
inline constexpr char kHideWidgetHistogramName[] = "Qorai.VPN.HideWidget";
inline constexpr char kVPNConnectedDurationHistogramName[] =
    "Qorai.VPN.ConnectedDuration";

class QoraiVpnMetrics {
 public:
  class Delegate {
   public:
    virtual ~Delegate() = default;

    virtual bool is_purchased_user() const = 0;

#if !BUILDFLAG(IS_ANDROID)
    virtual bool IsConnected() const = 0;
#endif
  };

  QoraiVpnMetrics(PrefService* local_prefs,
                  PrefService* profile_prefs,
                  base::WeakPtr<misc_metrics::UptimeMonitor> uptime_monitor,
                  Delegate* delegate = nullptr);
  ~QoraiVpnMetrics();

  QoraiVpnMetrics(const QoraiVpnMetrics&) = delete;
  QoraiVpnMetrics& operator=(const QoraiVpnMetrics&) = delete;

  // new_usage should be set to true if a new VPN connection was just
  // established.
  void RecordAllMetrics(bool new_usage);

#if BUILDFLAG(IS_ANDROID)
  void RecordAndroidBackgroundP3A(int64_t session_start_time_ms,
                                  int64_t session_end_time_ms);
#endif

  void RecordWidgetUsage(bool new_usage);

  // Records one minute of VPN connected time
  void RecordVPNConnectedInterval();

 private:
  void HandleShowWidgetChange();

  void ReportVPNConnectedDuration();

  raw_ptr<PrefService> local_state_;
  raw_ptr<PrefService> profile_prefs_;
  PrefChangeRegistrar pref_change_registrar_;
  base::WeakPtr<misc_metrics::UptimeMonitor> uptime_monitor_;
  raw_ptr<Delegate> delegate_ = nullptr;

  WeeklyStorage widget_usage_storage_;
  WeeklyStorage connected_minutes_storage_;
  base::WallClockTimer report_timer_;

  base::WallClockTimer connection_report_timer_;
};

}  // namespace qorai_vpn

#endif  // QORAI_COMPONENTS_QORAI_VPN_BROWSER_QORAI_VPN_METRICS_H_
