/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_BROWSING_DATA_CORE_PREF_NAMES_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_BROWSING_DATA_CORE_PREF_NAMES_H_

#include <components/browsing_data/core/pref_names.h>  // IWYU pragma: export

namespace browsing_data {

namespace prefs {

inline constexpr char kDeleteBrowsingHistoryOnExit[] =
    "browser.clear_data.browsing_history_on_exit";
inline constexpr char kDeleteDownloadHistoryOnExit[] =
    "browser.clear_data.download_history_on_exit";
inline constexpr char kDeleteCacheOnExit[] = "browser.clear_data.cache_on_exit";
inline constexpr char kDeleteCookiesOnExit[] =
    "browser.clear_data.cookies_on_exit";
inline constexpr char kDeletePasswordsOnExit[] =
    "browser.clear_data.passwords_on_exit";
inline constexpr char kDeleteFormDataOnExit[] =
    "browser.clear_data.form_data_on_exit";
inline constexpr char kDeleteHostedAppsDataOnExit[] =
    "browser.clear_data.hosted_apps_data_on_exit";
inline constexpr char kDeleteSiteSettingsOnExit[] =
    "browser.clear_data.site_settings_on_exit";
inline constexpr char kDeleteQoraiQoraHistory[] = "browser.clear_data.qoraiqora";
inline constexpr char kDeleteQoraiQoraHistoryOnExit[] =
    "browser.clear_data.qorai_qora_on_exit";

}  // namespace prefs

}  // namespace browsing_data

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_BROWSING_DATA_CORE_PREF_NAMES_H_
