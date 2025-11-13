/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ELIGIBLE_ADS_CALLBACK_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ELIGIBLE_ADS_CALLBACK_H_

#include "base/functional/callback.h"

namespace qorai_ads {

template <typename T>
using EligibleAdsCallback = base::OnceCallback<void(T eligible_ads)>;

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_SERVING_ELIGIBLE_ADS_ELIGIBLE_ADS_CALLBACK_H_
