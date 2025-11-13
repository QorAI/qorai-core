/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_MISC_METRICS_PROFILE_NEW_TAB_METRICS_H_
#define QORAI_BROWSER_MISC_METRICS_PROFILE_NEW_TAB_METRICS_H_

#include "components/prefs/pref_change_registrar.h"

class PrefService;

namespace misc_metrics {

inline constexpr char kNewTabPageDefaultHistogramName[] =
    "Qorai.NTP.DefaultPage";

enum class NewTabPageDefaultType {
  kDashboard = 0,
  kBlank = 1,
  kHomepageQoraiSearch = 2,
  kHomepageGoogle = 3,
  kHomepageDuckDuckGo = 4,
  kHomepageOther = 5,
  kMaxValue = kHomepageOther
};

class ProfileNewTabMetrics {
 public:
  explicit ProfileNewTabMetrics(PrefService* profile_prefs);
  ~ProfileNewTabMetrics();

  ProfileNewTabMetrics(const ProfileNewTabMetrics&) = delete;
  ProfileNewTabMetrics& operator=(const ProfileNewTabMetrics&) = delete;

 private:
  void ReportNewTabPageDefault();

  raw_ptr<PrefService> profile_prefs_;
  PrefChangeRegistrar pref_change_registrar_;
};

}  // namespace misc_metrics

#endif  // QORAI_BROWSER_MISC_METRICS_PROFILE_NEW_TAB_METRICS_H_
