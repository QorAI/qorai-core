/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_LEGACY_MIGRATION_DATABASE_DATABASE_CONSTANTS_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_LEGACY_MIGRATION_DATABASE_DATABASE_CONSTANTS_H_

namespace qorai_ads::database {

inline constexpr int kVersionNumber = 52;
inline constexpr int kCompatibleVersionNumber = 52;

// If the database version number is less than or equal to this value, the
// database will be razed and recreated during migration. This should be updated
// to match CR versions of the browser that no longer refill confirmation
// tokens.
inline constexpr int kRazeDatabaseThresholdVersionNumber = 32;

}  // namespace qorai_ads::database

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_LEGACY_MIGRATION_DATABASE_DATABASE_CONSTANTS_H_
