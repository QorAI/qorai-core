/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_WELCOME_PAGE_QORAI_WELCOME_UI_PREFS_H_
#define QORAI_BROWSER_UI_WEBUI_WELCOME_PAGE_QORAI_WELCOME_UI_PREFS_H_

class PrefRegistrySimple;
class PrefService;

namespace qorai::welcome_ui::prefs {

inline constexpr char kHasSeenQoraiWelcomePage[] =
    "qorai.has_seen_qorai_welcome_page";

void RegisterProfilePrefs(PrefRegistrySimple* registry);
void MigratePrefs(PrefService* prefs);

}  // namespace qorai::welcome_ui::prefs

#endif  // QORAI_BROWSER_UI_WEBUI_WELCOME_PAGE_QORAI_WELCOME_UI_PREFS_H_
