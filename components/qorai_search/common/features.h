// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_SEARCH_COMMON_FEATURES_H_
#define QORAI_COMPONENTS_QORAI_SEARCH_COMMON_FEATURES_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace qorai_search {
namespace features {

inline constexpr char kQoraiSearchDefaultAPIDailyLimitName[] =
    "QoraiSearchDefaultAPIDailyLimit";
inline constexpr char kQoraiSearchDefaultAPITotalLimitName[] =
    "QoraiSearchDefaultAPITotalLimit";

BASE_DECLARE_FEATURE(kQoraiSearchDefaultAPIFeature);
extern const base::FeatureParam<int> kQoraiSearchDefaultAPIDailyLimit;
extern const base::FeatureParam<int> kQoraiSearchDefaultAPITotalLimit;

// If enabled, the initial search page and subsequent redirected pages will
// all be rendered, instead of just the initial page.
BASE_DECLARE_FEATURE(kBackupResultsFullRender);
// The amount of requests required to reach the actual search engine
// results page. This count includes the original request and the subsequent
// redirects.
extern const base::FeatureParam<int> kBackupResultsFullRenderMaxRequests;

bool IsBackupResultsFullRenderEnabled();

}  // namespace features
}  // namespace qorai_search

#endif  // QORAI_COMPONENTS_QORAI_SEARCH_COMMON_FEATURES_H_
