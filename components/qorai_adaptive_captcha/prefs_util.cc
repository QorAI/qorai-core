/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_adaptive_captcha/prefs_util.h"

#include "qorai/components/qorai_adaptive_captcha/pref_names.h"
#include "components/prefs/pref_service.h"

namespace qorai_adaptive_captcha {

void MigrateObsoleteProfilePrefs(PrefService* prefs) {
  // Added 10/2024
  prefs->ClearPref(prefs::kScheduledCaptchaSnoozeCount);
}

}  // namespace qorai_adaptive_captcha
