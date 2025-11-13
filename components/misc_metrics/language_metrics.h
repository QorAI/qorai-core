/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_MISC_METRICS_LANGUAGE_METRICS_H_
#define QORAI_COMPONENTS_MISC_METRICS_LANGUAGE_METRICS_H_

#include "components/prefs/pref_change_registrar.h"

class PrefService;

namespace misc_metrics {

inline constexpr char kPrimaryLanguageHistogramName[] =
    "Qorai.Core.PrimaryLang";

class LanguageMetrics {
 public:
  explicit LanguageMetrics(PrefService* profile_prefs);
  ~LanguageMetrics();

  LanguageMetrics(const LanguageMetrics&) = delete;
  LanguageMetrics& operator=(const LanguageMetrics&) = delete;

 private:
  void RecordLanguageMetric();

  PrefChangeRegistrar pref_change_registrar_;
  raw_ptr<PrefService> profile_prefs_;
};

}  // namespace misc_metrics

#endif  // QORAI_COMPONENTS_MISC_METRICS_LANGUAGE_METRICS_H_
