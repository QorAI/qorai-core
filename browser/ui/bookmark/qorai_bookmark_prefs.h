/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_BOOKMARK_QORAI_BOOKMARK_PREFS_H_
#define QORAI_BROWSER_UI_BOOKMARK_QORAI_BOOKMARK_PREFS_H_

class PrefRegistrySimple;

namespace qorai::bookmarks::prefs {

inline constexpr char kShowAllBookmarksButton[] =
    "qorai.bookmarks.show_all_bookmarks_button";

void RegisterProfilePrefs(PrefRegistrySimple* registry);

}  // namespace qorai::bookmarks::prefs

#endif  // QORAI_BROWSER_UI_BOOKMARK_QORAI_BOOKMARK_PREFS_H_
