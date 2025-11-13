/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_CONVERSION_USER_DATA_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_CONVERSION_USER_DATA_UTIL_H_

#include <optional>

#include "base/values.h"

namespace qorai_ads {

struct ConversionInfo;

base::Value::Dict BuildConversionActionTypeUserData(
    const ConversionInfo& conversion);

std::optional<base::Value::Dict> MaybeBuildVerifiableConversionUserData(
    const ConversionInfo& conversion);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_CONVERSION_USER_DATA_UTIL_H_
