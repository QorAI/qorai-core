/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_STATEMENT_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_STATEMENT_UTIL_H_

#include <string>

namespace base {
class Time;
}  // namespace base

namespace qorai_ads::database {

// Convert a time to a SQL value.
std::string TimeToSqlValueAsString(base::Time time);

}  // namespace qorai_ads::database

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_COMMON_DATABASE_DATABASE_STATEMENT_UTIL_H_
