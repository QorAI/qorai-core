/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SIDEBAR_BROWSER_CONSTANTS_H_
#define QORAI_COMPONENTS_SIDEBAR_BROWSER_CONSTANTS_H_

namespace sidebar {

inline constexpr char kSidebarItemURLKey[] = "url";
inline constexpr char kSidebarItemTypeKey[] = "type";
inline constexpr char kSidebarItemBuiltInItemTypeKey[] = "built_in_item_type";
inline constexpr char kSidebarItemTitleKey[] = "title";
inline constexpr char kSidebarItemOpenInPanelKey[] = "open_in_panel";
inline constexpr int kDefaultSidePanelWidth = 320;

// list is provided from chrome layer.
inline constexpr char kQoraiTalkURL[] = "https://talk.qorai.com/widget";
inline constexpr char kQoraiTalkHost[] = "talk.qorai.com";

}  // namespace sidebar

#endif  // QORAI_COMPONENTS_SIDEBAR_BROWSER_CONSTANTS_H_
