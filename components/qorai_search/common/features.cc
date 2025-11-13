// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_search/common/features.h"

#include "base/feature_list.h"

namespace qorai_search::features {

BASE_FEATURE(kQoraiSearchDefaultAPIFeature,
             "QoraiSearchDefaultAPI",
             base::FEATURE_ENABLED_BY_DEFAULT);

const base::FeatureParam<int> kQoraiSearchDefaultAPIDailyLimit{
    &kQoraiSearchDefaultAPIFeature, kQoraiSearchDefaultAPIDailyLimitName, 3};

const base::FeatureParam<int> kQoraiSearchDefaultAPITotalLimit{
    &kQoraiSearchDefaultAPIFeature, kQoraiSearchDefaultAPITotalLimitName, 10};

BASE_FEATURE(kBackupResultsFullRender,
             "QoraiSearchBackupResultsFullRender",
             base::FEATURE_DISABLED_BY_DEFAULT);

const base::FeatureParam<int> kBackupResultsFullRenderMaxRequests{
    &kBackupResultsFullRender, "MaxRequests", 2};

bool IsBackupResultsFullRenderEnabled() {
  return base::FeatureList::IsEnabled(kBackupResultsFullRender);
}

}  // namespace qorai_search::features
