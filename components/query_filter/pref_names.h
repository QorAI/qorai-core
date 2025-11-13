// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QUERY_FILTER_PREF_NAMES_H_
#define QORAI_COMPONENTS_QUERY_FILTER_PREF_NAMES_H_

namespace query_filter {

// The preference to enable or disable known tracking query parameters filtering
// via policy.
inline constexpr char kTrackingQueryParametersFilteringEnabled[] =
    "qorai.tracking_query_parameters_filtering_enabled";

}  // namespace query_filter

#endif  // QORAI_COMPONENTS_QUERY_FILTER_PREF_NAMES_H_
