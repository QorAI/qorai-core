/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADAPTIVE_CAPTCHA_PREFS_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADAPTIVE_CAPTCHA_PREFS_UTIL_H_

class PrefService;

namespace qorai_adaptive_captcha {

void MigrateObsoleteProfilePrefs(PrefService* prefs);

}  // namespace qorai_adaptive_captcha

#endif  // QORAI_COMPONENTS_QORAI_ADAPTIVE_CAPTCHA_PREFS_UTIL_H_
