/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_welcome/common/features.h"

#include "base/feature_list.h"

namespace qorai_welcome::features {

BASE_FEATURE(kShowRewardsCard,
             base::FEATURE_DISABLED_BY_DEFAULT);

}  // namespace qorai_welcome::features
