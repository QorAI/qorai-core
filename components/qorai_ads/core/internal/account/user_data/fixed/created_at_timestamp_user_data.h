/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_CREATED_AT_TIMESTAMP_USER_DATA_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_CREATED_AT_TIMESTAMP_USER_DATA_H_

#include "base/values.h"

namespace qorai_ads {

struct TransactionInfo;

base::Value::Dict BuildCreatedAtTimestampUserData(
    const TransactionInfo& transaction);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_CREATED_AT_TIMESTAMP_USER_DATA_H_
