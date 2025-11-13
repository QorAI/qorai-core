/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_PRIVATE_NEW_TAB_UI_COMMON_PREF_NAMES_H_
#define QORAI_COMPONENTS_QORAI_PRIVATE_NEW_TAB_UI_COMMON_PREF_NAMES_H_

class PrefRegistrySimple;

namespace qorai_private_new_tab::prefs {

inline constexpr char kQoraiPrivateWindowDisclaimerDismissed[] =
    "qorai.qorai_private_new_tab.private_window_disclaimer_dismissed";
inline constexpr char kQoraiTorWindowDisclaimerDismissed[] =
    "qorai.qorai_private_new_tab.tor_window_disclaimer_dismissed";

void RegisterProfilePrefs(PrefRegistrySimple* registry);

}  // namespace qorai_private_new_tab::prefs

#endif  // QORAI_COMPONENTS_QORAI_PRIVATE_NEW_TAB_UI_COMMON_PREF_NAMES_H_
