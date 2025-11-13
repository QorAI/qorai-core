// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "qorai/components/qorai_search/common/qorai_search_utils.h"

#include <vector>

#include "base/feature_list.h"
#include "qorai/components/qorai_search/common/features.h"
#include "url/gurl.h"
#include "url/origin.h"
#include "url/url_constants.h"

namespace {

const std::vector<url::Origin>& OriginList() {
  static const base::NoDestructor<std::vector<url::Origin>> list([] {
    std::vector<url::Origin> list;
    std::ranges::transform(qorai_search::kVettedHosts, std::back_inserter(list),
                           [](auto& origin_string) {
                             return url::Origin::Create(GURL(origin_string));
                           });
    return list;
  }());
  return *list;
}

}  // namespace

namespace qorai_search {

bool IsAllowedHost(const GURL& origin) {
  if (!origin.is_valid() || !origin.SchemeIs(url::kHttpsScheme)) {
    return false;
  }
  const auto& safe_origins = OriginList();
  for (const url::Origin& safe_origin : safe_origins) {
    if (safe_origin.host() == origin.host()) {
      return true;
    }
  }
  return false;
}

bool IsDefaultAPIEnabled() {
  return base::FeatureList::IsEnabled(
      qorai_search::features::kQoraiSearchDefaultAPIFeature);
}

}  // namespace qorai_search
