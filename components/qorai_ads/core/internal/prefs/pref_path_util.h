/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_PREFS_PREF_PATH_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_PREFS_PREF_PATH_UTIL_H_

#include <string>

namespace qorai_ads {

bool DoesMatchUserHasJoinedQoraiRewardsPrefPath(const std::string& path);

bool DoesMatchUserHasOptedInToQoraiNewsAdsPrefPath(const std::string& path);

bool DoesMatchUserHasOptedInToNewTabPageAdsPrefPath(const std::string& path);

bool DoesMatchUserHasOptedInToNotificationAdsPrefPath(const std::string& path);

bool DoesMatchUserHasOptedInToSearchResultAdsPrefPath(const std::string& path);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_PREFS_PREF_PATH_UTIL_H_
