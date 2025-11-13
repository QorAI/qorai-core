/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/page_info/features.h"

namespace page_info::features {

BASE_FEATURE(kShowQoraiShieldsInPageInfo, base::FEATURE_DISABLED_BY_DEFAULT);

bool IsShowQoraiShieldsInPageInfoEnabled() {
  return base::FeatureList::IsEnabled(kShowQoraiShieldsInPageInfo);
}

}  // namespace page_info::features
