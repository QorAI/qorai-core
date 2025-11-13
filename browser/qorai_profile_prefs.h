/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_PROFILE_PREFS_H_
#define QORAI_BROWSER_QORAI_PROFILE_PREFS_H_

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace qorai {

void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

}  // namespace qorai

#endif  // QORAI_BROWSER_QORAI_PROFILE_PREFS_H_
