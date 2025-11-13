/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "base/check.h"
#include "chrome/browser/ui/singleton_tabs.h"
#include "components/sync_sessions/open_tabs_ui_delegate.h"
#include "ui/base/l10n/l10n_util.h"

namespace {

constexpr char kQoraiStubSessionTag[] = "qorai_stub_more_session_tag";
constexpr char kQoraiSyncedTabsUrl[] = "qorai://history/syncedTabs";

}  //  namespace

#define QORAI_RECENT_TABS_SUB_MENU_MODEL_BUILD_TABS_FROM_OTHER_DEVICES      \
  if (tabs_in_session.size() > kMaxSessionsToShow) {                        \
    /* Not all the tabs are shown in menu */                                \
    if (!stub_tab_.get()) {                                                 \
      stub_tab_.reset(new sessions::SessionTab());                          \
      sessions::SerializedNavigationEntry stub_nav_entry;                   \
      stub_nav_entry.set_title(                                             \
          l10n_util::GetStringUTF16(IDS_OPEN_MORE_OTHER_DEVICES_SESSIONS)); \
      stub_nav_entry.set_virtual_url(GURL(kQoraiSyncedTabsUrl));            \
      stub_tab_->navigations.push_back(stub_nav_entry);                     \
      stub_tab_->tab_id = SessionID::NewUnique();                           \
    }                                                                       \
    tabs_in_session[kMaxSessionsToShow] = stub_tab_.get();                  \
    BuildOtherDevicesTabItem(device_menu_model.get(), kQoraiStubSessionTag, \
                             *tabs_in_session[kMaxSessionsToShow]);         \
  }

// Do not show the menu item to signin to show tabs from other devices. Instead,
// always show the "No tabs from other devices" string.
#define GetAllForeignSessions(SESSIONS) GetAllForeignSessions(&sessions)) { \
    AddItemWithStringId(IDC_RECENT_TABS_NO_DEVICE_TABS,                     \
                        IDS_RECENT_TABS_NO_DEVICE_TABS);                    \
  }                                                                         \
  if (false

#include <chrome/browser/ui/tabs/recent_tabs_sub_menu_model.cc>

#undef GetAllForeignSessions
#undef QORAI_RECENT_TABS_SUB_MENU_MODEL_BUILD_TABS_FROM_OTHER_DEVICES

#include "qorai/browser/ui/toolbar/qorai_recent_tabs_sub_menu_model.h"

// Methods of QoraiRecentTabsSubMenuModel are implemented below instead of
// qorai_recent_tabs_sub_menu_model.cc to have the access to functions in
// anonymous namespace in recent_tabs_sub_menu_model.cc

QoraiRecentTabsSubMenuModel::QoraiRecentTabsSubMenuModel(
    ui::AcceleratorProvider* accelerator_provider,
    Browser* browser)
    : RecentTabsSubMenuModel(accelerator_provider, browser) {}

QoraiRecentTabsSubMenuModel::~QoraiRecentTabsSubMenuModel() {}

void QoraiRecentTabsSubMenuModel::ExecuteCommand(int command_id,
                                                 int event_flags) {
  if (IsCommandType(CommandType::Tab, command_id)) {
    const TabItems& tab_items = *GetTabVectorForCommandId(command_id);
    const TabItem& item = tab_items.at(command_id);
    DCHECK(item.tab_id.is_valid() && item.url.is_valid());

    if (item.session_tag == kQoraiStubSessionTag) {
      ShowSingletonTabOverwritingNTP(browser_, GURL(kQoraiSyncedTabsUrl));
      return;
    }
  }

  if (command_id == IDC_CLEAR_BROWSING_DATA) {
    chrome::ExecuteCommand(browser_, command_id);
    return;
  }

  RecentTabsSubMenuModel::ExecuteCommand(command_id, event_flags);
}
