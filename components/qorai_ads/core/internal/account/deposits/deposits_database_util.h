/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSITS_DATABASE_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSITS_DATABASE_UTIL_H_

namespace qorai_ads::database {

void PurgeExpiredDeposits();

}  // namespace qorai_ads::database

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSITS_DATABASE_UTIL_H_
