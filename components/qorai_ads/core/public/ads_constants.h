/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_ADS_CONSTANTS_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_ADS_CONSTANTS_H_

namespace qorai_ads {

inline constexpr char kTraceEventCategory[] = "qorai.ads";

inline constexpr char kDatabaseFilename[] = "database.sqlite";

// TODO(https://github.com/qorai/qorai-browser/issues/39795): Transition away
// from using JSON state to a more efficient data approach.
inline constexpr char kClientJsonFilename[] = "client.json";

// TODO(https://github.com/qorai/qorai-browser/issues/39795): Transition away
// from using JSON state to a more efficient data approach.
inline constexpr char kConfirmationsJsonFilename[] = "confirmations.json";

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_ADS_CONSTANTS_H_
