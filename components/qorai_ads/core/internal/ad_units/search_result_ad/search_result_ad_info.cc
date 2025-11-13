/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/ad_units/search_result_ad/search_result_ad_info.h"

namespace qorai_ads {

bool SearchResultAdInfo::IsValid() const {
  return AdInfo::IsValid() && !headline_text.empty() && !description.empty();
}

}  // namespace qorai_ads
