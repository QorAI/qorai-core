/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_STATS_FIRST_RUN_UTIL_H_
#define QORAI_BROWSER_QORAI_STATS_FIRST_RUN_UTIL_H_

#include "base/time/time.h"

class PrefService;

namespace qorai_stats {

#if BUILDFLAG(IS_ANDROID)
void ResetAndroidFirstRunStateForTesting();
#endif  // #BUILDFLAG(IS_ANDROID)

base::Time GetFirstRunTime(PrefService* local_state);
bool IsFirstRun(PrefService* local_state);

}  // namespace qorai_stats

#endif  // QORAI_BROWSER_QORAI_STATS_FIRST_RUN_UTIL_H_
