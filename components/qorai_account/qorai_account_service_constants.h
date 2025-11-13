/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ACCOUNT_QORAI_ACCOUNT_SERVICE_CONSTANTS_H_
#define QORAI_COMPONENTS_QORAI_ACCOUNT_QORAI_ACCOUNT_SERVICE_CONSTANTS_H_

#include "base/time/time.h"

namespace qorai_account {

inline constexpr base::TimeDelta kVerifyResultPollInterval = base::Seconds(5);
inline constexpr base::TimeDelta kVerifyResultWatchdogInterval =
    3 * kVerifyResultPollInterval;

}  // namespace qorai_account

#endif  // QORAI_COMPONENTS_QORAI_ACCOUNT_QORAI_ACCOUNT_SERVICE_CONSTANTS_H_
