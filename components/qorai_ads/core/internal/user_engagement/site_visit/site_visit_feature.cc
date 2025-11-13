/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/public/user_engagement/site_visit/site_visit_feature.h"

namespace qorai_ads {

BASE_FEATURE(kSiteVisitFeature, "SiteVisit", base::FEATURE_ENABLED_BY_DEFAULT);

}  // namespace qorai_ads
