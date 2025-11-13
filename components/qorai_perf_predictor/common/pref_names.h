/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_PERF_PREDICTOR_COMMON_PREF_NAMES_H_
#define QORAI_COMPONENTS_QORAI_PERF_PREDICTOR_COMMON_PREF_NAMES_H_

namespace qorai_perf_predictor {

namespace prefs {

inline constexpr char kBandwidthSavedBytes[] =
    "qorai.stats.bandwidth_saved_bytes";
inline constexpr char kBandwidthSavedDailyBytes[] =
    "qorai.stats.daily_saving_predictions_bytes";

}  // namespace prefs

}  // namespace qorai_perf_predictor

#endif  // QORAI_COMPONENTS_QORAI_PERF_PREDICTOR_COMMON_PREF_NAMES_H_
