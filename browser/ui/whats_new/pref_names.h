/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WHATS_NEW_PREF_NAMES_H_
#define QORAI_BROWSER_UI_WHATS_NEW_PREF_NAMES_H_

namespace whats_new::prefs {

// Store lastly shown whats-new version - major version.
// Ex, "1.50" means browser launched whats-new page for v1.50 update already.
inline constexpr char kWhatsNewLastVersion[] = "qorai.whats_new.last_version";

}  // namespace whats_new::prefs

#endif  // QORAI_BROWSER_UI_WHATS_NEW_PREF_NAMES_H_
