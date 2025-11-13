/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/qorai_browser_command_controller.h"

#include <optional>

#include "base/check.h"
#include "base/check_is_test.h"
#include "base/containers/fixed_flat_set.h"
#include "base/feature_list.h"
#include "base/logging.h"
#include "base/notreached.h"
#include "base/types/to_address.h"
#include "qorai/app/qorai_command_ids.h"
#include "qorai/browser/ai_chat/ai_chat_utils.h"
#include "qorai/browser/profiles/profile_util.h"
#include "qorai/browser/ui/qorai_pages.h"
#include "qorai/browser/ui/browser_commands.h"
#include "qorai/browser/ui/sidebar/sidebar_utils.h"
#include "qorai/browser/ui/tabs/features.h"
#include "qorai/components/ai_chat/core/browser/utils.h"
#include "qorai/components/ai_chat/core/common/features.h"
#include "qorai/components/ai_chat/core/common/pref_names.h"
#include "qorai/components/qorai_news/common/pref_names.h"
#include "qorai/components/qorai_rewards/core/rewards_util.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "qorai/components/qorai_wallet/common/common_utils.h"
#include "qorai/components/qorai_wayback_machine/buildflags/buildflags.h"
#include "qorai/components/commander/common/buildflags/buildflags.h"
#include "qorai/components/commands/common/features.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/playlist/core/common/buildflags/buildflags.h"
#include "qorai/components/speedreader/common/buildflags/buildflags.h"
#include "chrome/app/chrome_command_ids.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/send_tab_to_self/send_tab_to_self_util.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_command_controller.h"
#include "chrome/browser/ui/browser_commands.h"
#include "chrome/browser/ui/browser_window/public/browser_window_features.h"
#include "chrome/browser/ui/tabs/tab_change_type.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "chrome/browser/ui/tabs/tab_strip_model_observer.h"
#include "chrome/browser/ui/ui_features.h"
#include "chrome/common/pref_names.h"
#include "components/prefs/pref_service.h"
#include "components/sync/base/command_line_switches.h"
#include "content/public/browser/web_contents.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/browser/qorai_vpn/qorai_vpn_service_factory.h"
#include "qorai/browser/qorai_vpn/vpn_utils.h"
#include "qorai/components/qorai_vpn/browser/qorai_vpn_service.h"
#include "qorai/components/qorai_vpn/common/pref_names.h"
#endif

#if BUILDFLAG(ENABLE_SPEEDREADER)
#include "qorai/components/speedreader/common/features.h"
#endif

#if BUILDFLAG(ENABLE_PLAYLIST_WEBUI)
#include "qorai/browser/playlist/playlist_service_factory.h"
#include "qorai/components/playlist/core/common/features.h"
#endif

#if BUILDFLAG(ENABLE_COMMANDER)
#include "qorai/browser/ui/commander/commander_service.h"
#endif

#if BUILDFLAG(ENABLE_TOR)
#include "qorai/browser/tor/tor_profile_service_factory.h"
#endif

namespace {

bool IsQoraiCommands(int id) {
  return id >= IDC_QORAI_COMMANDS_START && id <= IDC_QORAI_COMMANDS_LAST;
}

bool IsQoraiOverrideCommands(int id) {
  static constexpr auto kOverrideCommands = base::MakeFixedFlatSet<int>({
      IDC_NEW_WINDOW,
      IDC_NEW_INCOGNITO_WINDOW,
      IDC_TOGGLE_VERTICAL_TABS,
  });
  return kOverrideCommands.contains(id);
}

}  // namespace

namespace chrome {

QoraiBrowserCommandController::QoraiBrowserCommandController(
    BrowserWindowInterface* bwi)
    : BrowserCommandController(bwi),
      browser_(*bwi->GetBrowserForMigrationOnly()),
      qorai_command_updater_(nullptr) {
  InitQoraiCommandState();
#if BUILDFLAG(ENABLE_QORAI_VPN)
  if (auto* vpn_service = qorai_vpn::QoraiVpnServiceFactory::GetForProfile(
          browser_->profile())) {
    qorai_vpn::QoraiVPNServiceObserver::Observe(vpn_service);
  }
#endif
}

QoraiBrowserCommandController::~QoraiBrowserCommandController() = default;

void QoraiBrowserCommandController::TabChangedAt(content::WebContents* contents,
                                                 int index,
                                                 TabChangeType type) {
  UpdateCommandEnabled(IDC_CLOSE_DUPLICATE_TABS,
                       qorai::HasDuplicateTabs(&*browser_));
  UpdateCommandsForTabs();
  UpdateCommandsForSend();
}

void QoraiBrowserCommandController::TabPinnedStateChanged(
    TabStripModel* tab_strip_model,
    content::WebContents* contents,
    int index) {
  UpdateCommandsForPin();
}

void QoraiBrowserCommandController::OnTabStripModelChanged(
    TabStripModel* tab_strip_model,
    const TabStripModelChange& change,
    const TabStripSelectionChange& selection) {
  BrowserCommandController::OnTabStripModelChanged(tab_strip_model, change,
                                                   selection);

  UpdateCommandEnabled(IDC_WINDOW_CLOSE_TABS_TO_LEFT,
                       qorai::CanCloseTabsToLeft(&*browser_));
  UpdateCommandEnabled(IDC_CLOSE_DUPLICATE_TABS,
                       qorai::HasDuplicateTabs(&*browser_));
  UpdateCommandsForTabs();
  UpdateCommandsForSend();
  UpdateCommandsForPin();

  if (base::FeatureList::IsEnabled(features::kSideBySide) &&
      browser_->is_type_normal() && selection.active_tab_changed()) {
    UpdateCommandForSplitView();
  }
}

void QoraiBrowserCommandController::OnSplitTabChanged(
    const SplitTabChange& change) {
  UpdateCommandForSplitView();
}

void QoraiBrowserCommandController::OnTabGroupChanged(
    const TabGroupChange& change) {
  UpdateCommandsForTabs();
}

bool QoraiBrowserCommandController::SupportsCommand(int id) const {
  return IsQoraiCommands(id) ? qorai_command_updater_.SupportsCommand(id)
                             : BrowserCommandController::SupportsCommand(id);
}

bool QoraiBrowserCommandController::IsCommandEnabled(int id) const {
  return IsQoraiCommands(id) ? qorai_command_updater_.IsCommandEnabled(id)
                             : BrowserCommandController::IsCommandEnabled(id);
}

bool QoraiBrowserCommandController::ExecuteCommandWithDisposition(
    int id,
    WindowOpenDisposition disposition,
    base::TimeTicks time_stamp) {
  return IsQoraiCommands(id) || IsQoraiOverrideCommands(id)
             ? ExecuteQoraiCommandWithDisposition(id, disposition, time_stamp)
             : BrowserCommandController::ExecuteCommandWithDisposition(
                   id, disposition, time_stamp);
}

void QoraiBrowserCommandController::AddCommandObserver(
    int id,
    CommandObserver* observer) {
  IsQoraiCommands(id)
      ? qorai_command_updater_.AddCommandObserver(id, observer)
      : BrowserCommandController::AddCommandObserver(id, observer);
}

void QoraiBrowserCommandController::RemoveCommandObserver(
    int id,
    CommandObserver* observer) {
  IsQoraiCommands(id)
      ? qorai_command_updater_.RemoveCommandObserver(id, observer)
      : BrowserCommandController::RemoveCommandObserver(id, observer);
}

void QoraiBrowserCommandController::RemoveCommandObserver(
    CommandObserver* observer) {
  qorai_command_updater_.RemoveCommandObserver(observer);
  BrowserCommandController::RemoveCommandObserver(observer);
}

bool QoraiBrowserCommandController::UpdateCommandEnabled(int id, bool state) {
  return IsQoraiCommands(id)
             ? qorai_command_updater_.UpdateCommandEnabled(id, state)
             : BrowserCommandController::UpdateCommandEnabled(id, state);
}

void QoraiBrowserCommandController::InitQoraiCommandState() {
  // Sync, Rewards, and Wallet pages don't work in tor(guest) sessions.
  // They also don't work in private windows but they are redirected
  // to a normal window in this case.
  const bool is_guest_session = browser_->profile()->IsGuestSession();
  if (!is_guest_session) {
    // If Rewards is not supported due to OFAC sanctions we still want to show
    // the menu item.
    if (qorai_rewards::IsSupported(browser_->profile()->GetPrefs())) {
      UpdateCommandForQoraiRewards();
    }
    if (qorai_wallet::IsAllowed(browser_->profile()->GetPrefs())) {
      UpdateCommandForQoraiWallet();
    }
    if (syncer::IsSyncAllowedByFlag()) {
      UpdateCommandForQoraiSync();
    }
  }
  UpdateCommandForWebcompatReporter();
#if BUILDFLAG(ENABLE_TOR)
  UpdateCommandForTor();
#endif
  UpdateCommandForSidebar();
  UpdateCommandForQoraiVPN();
  UpdateCommandForPlaylist();
  UpdateCommandForWaybackMachine();
  pref_change_registrar_.Init(browser_->profile()->GetPrefs());

  UpdateCommandForAIChat();
  if (ai_chat::IsAllowedForContext(browser_->profile(), false)) {
    pref_change_registrar_.Add(
        ai_chat::prefs::kEnabledByPolicy,
        base::BindRepeating(
            &QoraiBrowserCommandController::UpdateCommandForAIChat,
            base::Unretained(this)));
  }

#if BUILDFLAG(ENABLE_QORAI_VPN)
  if (qorai_vpn::IsAllowedForContext(browser_->profile())) {
    pref_change_registrar_.Add(
        qorai_vpn::prefs::kManagedQoraiVPNDisabled,
        base::BindRepeating(
            &QoraiBrowserCommandController::UpdateCommandForQoraiVPN,
            base::Unretained(this)));
  }
#endif
  bool add_new_profile_enabled = !is_guest_session;
  bool open_guest_profile_enabled = !is_guest_session;
  if (!is_guest_session) {
    if (PrefService* local_state = g_browser_process->local_state()) {
      add_new_profile_enabled =
          local_state->GetBoolean(prefs::kBrowserAddPersonEnabled);
      open_guest_profile_enabled =
          local_state->GetBoolean(prefs::kBrowserGuestModeEnabled);
    }
  }
  UpdateCommandEnabled(IDC_ADD_NEW_PROFILE, add_new_profile_enabled);
  UpdateCommandEnabled(IDC_OPEN_GUEST_PROFILE, open_guest_profile_enabled);
  UpdateCommandEnabled(IDC_COPY_CLEAN_LINK, true);
  UpdateCommandEnabled(IDC_TOGGLE_TAB_MUTE, true);

#if BUILDFLAG(ENABLE_SPEEDREADER)
  if (base::FeatureList::IsEnabled(
          speedreader::features::kSpeedreaderFeature)) {
    UpdateCommandEnabled(IDC_SPEEDREADER_ICON_ONCLICK, true);
  }
#endif

#if BUILDFLAG(ENABLE_COMMANDER)
  UpdateCommandEnabled(IDC_COMMANDER, commander::IsEnabled());
#endif

  UpdateCommandEnabled(IDC_SHOW_APPS_PAGE,
                       !browser_->profile()->IsPrimaryOTRProfile());

  UpdateCommandEnabled(IDC_QORAI_BOOKMARK_BAR_SUBMENU, true);

  UpdateCommandEnabled(IDC_TOGGLE_VERTICAL_TABS, true);
  UpdateCommandEnabled(IDC_TOGGLE_VERTICAL_TABS_WINDOW_TITLE, true);
  UpdateCommandEnabled(IDC_TOGGLE_VERTICAL_TABS_EXPANDED, true);

  UpdateCommandEnabled(IDC_CONFIGURE_QORAI_NEWS,
                       !browser_->profile()->IsOffTheRecord() &&
                           !browser_->profile()->GetPrefs()->GetBoolean(
                               qorai_news::prefs::kQoraiNewsDisabledByPolicy));

  UpdateCommandEnabled(
      IDC_CONFIGURE_SHORTCUTS,
      base::FeatureList::IsEnabled(commands::features::kQoraiCommands));

  UpdateCommandEnabled(
      IDC_SHOW_QORAI_TALK,
      !browser_->profile()->GetPrefs()->GetBoolean(kQoraiTalkDisabledByPolicy));
  UpdateCommandEnabled(IDC_TOGGLE_SHIELDS, true);
  UpdateCommandEnabled(IDC_TOGGLE_JAVASCRIPT, true);

  UpdateCommandEnabled(IDC_CLOSE_DUPLICATE_TABS,
                       qorai::HasDuplicateTabs(&*browser_));
  UpdateCommandEnabled(IDC_WINDOW_ADD_ALL_TABS_TO_NEW_GROUP, true);

  UpdateCommandEnabled(IDC_SCROLL_TAB_TO_TOP, true);
  UpdateCommandEnabled(IDC_SCROLL_TAB_TO_BOTTOM, true);

  UpdateCommandEnabled(IDC_QORAI_SEND_TAB_TO_SELF, true);

  UpdateCommandsForTabs();
  UpdateCommandsForSend();
  UpdateCommandsForPin();

  UpdateCommandEnabled(IDC_TOGGLE_ALL_BOOKMARKS_BUTTON_VISIBILITY, true);
  UpdateCommandEnabled(IDC_EXPORT_ALL_BOOKMARKS, true);

  if (browser_->is_type_normal()) {
    // Delete these when upstream enables by default.
    UpdateCommandEnabled(IDC_READING_LIST_MENU, true);
    UpdateCommandEnabled(IDC_READING_LIST_MENU_ADD_TAB, true);
    UpdateCommandEnabled(IDC_READING_LIST_MENU_SHOW_UI, true);
  }
}

void QoraiBrowserCommandController::UpdateCommandForQoraiRewards() {
  UpdateCommandEnabled(IDC_SHOW_QORAI_REWARDS, true);
}

void QoraiBrowserCommandController::UpdateCommandForWebcompatReporter() {
  UpdateCommandEnabled(IDC_SHOW_QORAI_WEBCOMPAT_REPORTER, true);
}

#if BUILDFLAG(ENABLE_TOR)
void QoraiBrowserCommandController::UpdateCommandForTor() {
  // Enable new tor connection only for tor profile.
  UpdateCommandEnabled(IDC_NEW_TOR_CONNECTION_FOR_SITE,
                       browser_->profile()->IsTor());
  UpdateCommandEnabled(
      IDC_NEW_OFFTHERECORD_WINDOW_TOR,
      !TorProfileServiceFactory::IsTorDisabled(browser_->profile()));
}
#endif

void QoraiBrowserCommandController::UpdateCommandForSidebar() {
  if (sidebar::CanUseSidebar(&*browser_)) {
    UpdateCommandEnabled(IDC_SIDEBAR_SHOW_OPTION_MENU, true);
    UpdateCommandEnabled(IDC_SIDEBAR_TOGGLE_POSITION, true);
    UpdateCommandEnabled(IDC_TOGGLE_SIDEBAR, true);
  }
}

void QoraiBrowserCommandController::UpdateCommandForAIChat() {
  // AI Chat command implementation needs sidebar
  bool allowed_for_context = ai_chat::IsAllowedForContext(browser_->profile());
  UpdateCommandEnabled(IDC_TOGGLE_AI_CHAT, sidebar::CanUseSidebar(&*browser_) &&
                                               allowed_for_context);
  UpdateCommandEnabled(
      IDC_OPEN_FULL_PAGE_CHAT,
      ai_chat::features::IsAIChatHistoryEnabled() && allowed_for_context);
}

void QoraiBrowserCommandController::UpdateCommandForQoraiVPN() {
#if BUILDFLAG(ENABLE_QORAI_VPN)
  if (!qorai_vpn::IsQoraiVPNEnabled(browser_->profile())) {
    UpdateCommandEnabled(IDC_SHOW_QORAI_VPN_PANEL, false);
    UpdateCommandEnabled(IDC_QORAI_VPN_MENU, false);
    UpdateCommandEnabled(IDC_TOGGLE_QORAI_VPN_TOOLBAR_BUTTON, false);
    UpdateCommandEnabled(IDC_SEND_QORAI_VPN_FEEDBACK, false);
    UpdateCommandEnabled(IDC_ABOUT_QORAI_VPN, false);
    UpdateCommandEnabled(IDC_MANAGE_QORAI_VPN_PLAN, false);
    UpdateCommandEnabled(IDC_TOGGLE_QORAI_VPN, false);
#if BUILDFLAG(IS_WIN)
    UpdateCommandEnabled(IDC_TOGGLE_QORAI_VPN_TRAY_ICON, false);
#endif
    return;
  }
  UpdateCommandEnabled(IDC_SHOW_QORAI_VPN_PANEL, true);
  UpdateCommandEnabled(IDC_TOGGLE_QORAI_VPN_TOOLBAR_BUTTON, true);
#if BUILDFLAG(IS_WIN)
  UpdateCommandEnabled(IDC_TOGGLE_QORAI_VPN_TRAY_ICON, true);
#endif
  UpdateCommandEnabled(IDC_SEND_QORAI_VPN_FEEDBACK, true);
  UpdateCommandEnabled(IDC_ABOUT_QORAI_VPN, true);
  UpdateCommandEnabled(IDC_MANAGE_QORAI_VPN_PLAN, true);

  if (auto* vpn_service = qorai_vpn::QoraiVpnServiceFactory::GetForProfile(
          browser_->profile())) {
    // Only show vpn sub menu for purchased user.
    UpdateCommandEnabled(IDC_QORAI_VPN_MENU, vpn_service->is_purchased_user());
    UpdateCommandEnabled(IDC_TOGGLE_QORAI_VPN,
                         vpn_service->is_purchased_user());
  }
#endif
}

void QoraiBrowserCommandController::UpdateCommandForPlaylist() {
#if BUILDFLAG(ENABLE_PLAYLIST_WEBUI)
  if (base::FeatureList::IsEnabled(playlist::features::kPlaylist)) {
    UpdateCommandEnabled(
        IDC_SHOW_PLAYLIST_BUBBLE,
        browser_->is_type_normal() &&
            playlist::PlaylistServiceFactory::GetForBrowserContext(
                browser_->profile()));
  }
#endif
}

void QoraiBrowserCommandController::UpdateCommandForWaybackMachine() {
#if BUILDFLAG(ENABLE_QORAI_WAYBACK_MACHINE)
  UpdateCommandEnabled(IDC_SHOW_WAYBACK_MACHINE_BUBBLE, true);
#endif
}

void QoraiBrowserCommandController::UpdateCommandsForTabs() {
  UpdateCommandEnabled(IDC_WINDOW_MUTE_ALL_TABS,
                       qorai::CanMuteAllTabs(&*browser_, false));
  UpdateCommandEnabled(IDC_WINDOW_MUTE_OTHER_TABS,
                       qorai::CanMuteAllTabs(&*browser_, true));
  UpdateCommandEnabled(IDC_WINDOW_UNMUTE_ALL_TABS,
                       qorai::CanUnmuteAllTabs(&*browser_));

  UpdateCommandEnabled(IDC_GROUP_TABS_ON_CURRENT_ORIGIN, true);
  UpdateCommandEnabled(IDC_MOVE_GROUP_TO_NEW_WINDOW, true);

  bool is_in_group = qorai::IsInGroup(&*browser_);
  bool has_ungrouped_tabs = qorai::HasUngroupedTabs(&*browser_);
  UpdateCommandEnabled(IDC_WINDOW_GROUP_UNGROUPED_TABS, has_ungrouped_tabs);
  UpdateCommandEnabled(IDC_WINDOW_UNGROUP_GROUP, is_in_group);
  UpdateCommandEnabled(IDC_WINDOW_REMOVE_TAB_FROM_GROUP, is_in_group);
  UpdateCommandEnabled(IDC_WINDOW_NAME_GROUP, is_in_group);
  UpdateCommandEnabled(IDC_WINDOW_NEW_TAB_IN_GROUP, is_in_group);
  UpdateCommandEnabled(IDC_WINDOW_UNGROUP_ALL_TABS,
                       qorai::CanUngroupAllTabs(&*browser_));
  UpdateCommandEnabled(IDC_WINDOW_TOGGLE_GROUP_EXPANDED, is_in_group);
  UpdateCommandEnabled(IDC_WINDOW_CLOSE_UNGROUPED_TABS, has_ungrouped_tabs);
  UpdateCommandEnabled(IDC_WINDOW_CLOSE_TABS_NOT_IN_CURRENT_GROUP, is_in_group);
  UpdateCommandEnabled(IDC_WINDOW_CLOSE_GROUP, is_in_group);

  UpdateCommandEnabled(IDC_WINDOW_BRING_ALL_TABS,
                       qorai::CanBringAllTabs(&*browser_));
}

void QoraiBrowserCommandController::UpdateCommandsForSend() {
  UpdateCommandEnabled(
      IDC_QORAI_SEND_TAB_TO_SELF,
      send_tab_to_self::ShouldDisplayEntryPoint(
          browser_->tab_strip_model()->GetActiveWebContents()));
}

void QoraiBrowserCommandController::UpdateCommandsForPin() {
  UpdateCommandEnabled(IDC_WINDOW_CLOSE_UNPINNED_TABS,
                       qorai::CanCloseUnpinnedTabs(&*browser_));
}

void QoraiBrowserCommandController::UpdateCommandForSplitView() {
  // Some upstream unit test calls split tab apis w/o enabling SideBySide
  // feature.
  if (!base::FeatureList::IsEnabled(features::kSideBySide)) {
    CHECK_IS_TEST();
    return;
  }

  UpdateCommandEnabled(
      IDC_NEW_SPLIT_VIEW,
      qorai::CanOpenNewSplitTabsWithSideBySide(base::to_address(browser_)));
  UpdateCommandEnabled(IDC_TILE_TABS, qorai::CanSplitTabsWithSideBySide(
                                          base::to_address(browser_)));

  const bool is_split_tabs = qorai::IsSplitTabs(base::to_address(browser_));
  for (auto command_enabled_when_tab_is_split :
       {IDC_BREAK_TILE, IDC_SWAP_SPLIT_VIEW}) {
    UpdateCommandEnabled(command_enabled_when_tab_is_split, is_split_tabs);
  }
}

void QoraiBrowserCommandController::UpdateCommandForQoraiSync() {
  UpdateCommandEnabled(IDC_SHOW_QORAI_SYNC, true);
}

void QoraiBrowserCommandController::UpdateCommandForQoraiWallet() {
  UpdateCommandEnabled(IDC_SHOW_QORAI_WALLET, true);
  UpdateCommandEnabled(IDC_SHOW_QORAI_WALLET_PANEL, true);
  UpdateCommandEnabled(IDC_CLOSE_QORAI_WALLET_PANEL, true);
}

bool QoraiBrowserCommandController::ExecuteQoraiCommandWithDisposition(
    int id,
    WindowOpenDisposition disposition,
    base::TimeTicks time_stamp) {
  if (!SupportsCommand(id) || !IsCommandEnabled(id)) {
    return false;
  }

  if (browser_->tab_strip_model()->active_index() == TabStripModel::kNoTab) {
    return true;
  }

  DCHECK(IsCommandEnabled(id)) << "Invalid/disabled command " << id;

  switch (id) {
    case IDC_NEW_WINDOW:
      // Use chromium's action for non-Tor profiles.
      if (!browser_->profile()->IsTor()) {
        return BrowserCommandController::ExecuteCommandWithDisposition(
            id, disposition, time_stamp);
      }
      NewEmptyWindow(browser_->profile()->GetOriginalProfile());
      break;
    case IDC_NEW_INCOGNITO_WINDOW:
      // Use chromium's action for non-Tor profiles.
      if (!browser_->profile()->IsTor()) {
        return BrowserCommandController::ExecuteCommandWithDisposition(
            id, disposition, time_stamp);
      }
      NewIncognitoWindow(browser_->profile()->GetOriginalProfile());
      break;
    case IDC_SHOW_QORAI_REWARDS:
      qorai::ShowQoraiRewards(&*browser_);
      break;
    case IDC_SHOW_QORAI_WEBCOMPAT_REPORTER:
      qorai::ShowWebcompatReporter(&*browser_);
      break;
#if BUILDFLAG(ENABLE_TOR)
    case IDC_NEW_OFFTHERECORD_WINDOW_TOR:
      qorai::NewOffTheRecordWindowTor(&*browser_);
      break;
    case IDC_NEW_TOR_CONNECTION_FOR_SITE:
      qorai::NewTorConnectionForSite(&*browser_);
      break;
#endif
    case IDC_SHOW_QORAI_SYNC:
      qorai::ShowSync(&*browser_);
      break;
    case IDC_SHOW_QORAI_WALLET:
      qorai::ShowQoraiWallet(&*browser_);
      break;
    case IDC_TOGGLE_AI_CHAT:
      qorai::ToggleAIChat(&*browser_);
      break;
    case IDC_OPEN_FULL_PAGE_CHAT:
      qorai::ShowFullpageChat(&*browser_);
      break;
    case IDC_SPEEDREADER_ICON_ONCLICK:
      qorai::MaybeDistillAndShowSpeedreaderBubble(&*browser_);
      break;
    case IDC_SHOW_QORAI_WALLET_PANEL:
      qorai::ShowWalletBubble(&*browser_);
      break;
    case IDC_CLOSE_QORAI_WALLET_PANEL:
      qorai::CloseWalletBubble(&*browser_);
      break;
    case IDC_SHOW_QORAI_VPN_PANEL:
      qorai::ShowQoraiVPNBubble(&*browser_);
      break;
    case IDC_TOGGLE_QORAI_VPN_TRAY_ICON:
      qorai::ToggleQoraiVPNTrayIcon();
      break;
    case IDC_TOGGLE_QORAI_VPN_TOOLBAR_BUTTON:
      qorai::ToggleQoraiVPNButton(&*browser_);
      break;
    case IDC_SEND_QORAI_VPN_FEEDBACK:
    case IDC_ABOUT_QORAI_VPN:
    case IDC_MANAGE_QORAI_VPN_PLAN:
      qorai::OpenQoraiVPNUrls(&*browser_, id);
      break;
    case IDC_SIDEBAR_TOGGLE_POSITION:
      qorai::ToggleSidebarPosition(&*browser_);
      break;
    case IDC_TOGGLE_SIDEBAR:
      qorai::ToggleSidebar(&*browser_);
      break;
    case IDC_COPY_CLEAN_LINK:
      qorai::CopySanitizedURL(
          &*browser_,
          browser_->tab_strip_model()->GetActiveWebContents()->GetVisibleURL());
      break;
    case IDC_TOGGLE_TAB_MUTE:
      qorai::ToggleActiveTabAudioMute(&*browser_);
      break;
    case IDC_TOGGLE_VERTICAL_TABS:
      qorai::ToggleVerticalTabStrip(&*browser_);
      break;
    case IDC_TOGGLE_VERTICAL_TABS_WINDOW_TITLE:
      qorai::ToggleWindowTitleVisibilityForVerticalTabs(&*browser_);
      break;
    case IDC_TOGGLE_VERTICAL_TABS_EXPANDED:
      qorai::ToggleVerticalTabStripExpanded(&*browser_);
      break;
    case IDC_CONFIGURE_QORAI_NEWS:
      qorai::ShowQoraiNewsConfigure(&*browser_);
      break;
    case IDC_CONFIGURE_SHORTCUTS:
      qorai::ShowShortcutsPage(&*browser_);
      break;
    case IDC_SHOW_QORAI_TALK:
      qorai::ShowQoraiTalk(&*browser_);
      break;
    case IDC_TOGGLE_SHIELDS:
      qorai::ToggleShieldsEnabled(&*browser_);
      break;
    case IDC_TOGGLE_JAVASCRIPT:
      qorai::ToggleJavascriptEnabled(&*browser_);
      break;
    case IDC_SHOW_PLAYLIST_BUBBLE:
#if BUILDFLAG(ENABLE_PLAYLIST_WEBUI)
      qorai::ShowPlaylistBubble(&*browser_);
#else
      NOTREACHED() << " This command shouldn't be enabled";
#endif
      break;
    case IDC_SHOW_WAYBACK_MACHINE_BUBBLE:
#if BUILDFLAG(ENABLE_QORAI_WAYBACK_MACHINE)
      qorai::ShowWaybackMachineBubble(&*browser_);
#endif
      break;
    case IDC_GROUP_TABS_ON_CURRENT_ORIGIN:
      qorai::GroupTabsOnCurrentOrigin(&*browser_);
      break;
    case IDC_MOVE_GROUP_TO_NEW_WINDOW:
      qorai::MoveGroupToNewWindow(&*browser_);
      break;
    case IDC_CLOSE_DUPLICATE_TABS:
      qorai::CloseDuplicateTabs(&*browser_);
      break;
    case IDC_WINDOW_CLOSE_TABS_TO_LEFT:
      qorai::CloseTabsToLeft(&*browser_);
      break;
    case IDC_WINDOW_CLOSE_UNPINNED_TABS:
      qorai::CloseUnpinnedTabs(&*browser_);
      break;
    case IDC_WINDOW_ADD_ALL_TABS_TO_NEW_GROUP:
      qorai::AddAllTabsToNewGroup(&*browser_);
      break;
    case IDC_WINDOW_MUTE_ALL_TABS:
      qorai::MuteAllTabs(&*browser_, false);
      break;
    case IDC_WINDOW_MUTE_OTHER_TABS:
      qorai::MuteAllTabs(&*browser_, true);
      break;
    case IDC_WINDOW_UNMUTE_ALL_TABS:
      qorai::UnmuteAllTabs(&*browser_);
      break;
    case IDC_SCROLL_TAB_TO_TOP:
      qorai::ScrollTabToTop(&*browser_);
      break;
    case IDC_SCROLL_TAB_TO_BOTTOM:
      qorai::ScrollTabToBottom(&*browser_);
      break;
    case IDC_QORAI_SEND_TAB_TO_SELF:
      chrome::SendTabToSelf(&*browser_);
      break;
    case IDC_TOGGLE_ALL_BOOKMARKS_BUTTON_VISIBILITY:
      qorai::ToggleAllBookmarksButtonVisibility(base::to_address(browser_));
      break;
    case IDC_EXPORT_ALL_BOOKMARKS:
      qorai::ExportAllBookmarks(&*browser_);
      break;
    case IDC_COMMANDER:
#if BUILDFLAG(ENABLE_COMMANDER)
      qorai::ToggleCommander(base::to_address(browser_));
#endif
      break;
    case IDC_SHOW_APPS_PAGE:
      qorai::ShowAppsPage(&*browser_);
      break;
    case IDC_WINDOW_GROUP_UNGROUPED_TABS:
      qorai::GroupUngroupedTabs(&*browser_);
      break;
    case IDC_WINDOW_UNGROUP_GROUP:
      qorai::UngroupCurrentGroup(&*browser_);
      break;
    case IDC_WINDOW_REMOVE_TAB_FROM_GROUP:
      qorai::RemoveTabFromGroup(&*browser_);
      break;
    case IDC_WINDOW_UNGROUP_ALL_TABS:
      qorai::UngroupAllTabs(&*browser_);
      break;
    case IDC_WINDOW_NAME_GROUP:
      qorai::NameGroup(&*browser_);
      break;
    case IDC_WINDOW_NEW_TAB_IN_GROUP:
      qorai::NewTabInGroup(&*browser_);
      break;
    case IDC_WINDOW_TOGGLE_GROUP_EXPANDED:
      qorai::ToggleGroupExpanded(&*browser_);
      break;
    case IDC_WINDOW_CLOSE_UNGROUPED_TABS:
      qorai::CloseUngroupedTabs(&*browser_);
      break;
    case IDC_WINDOW_CLOSE_TABS_NOT_IN_CURRENT_GROUP:
      qorai::CloseTabsNotInCurrentGroup(&*browser_);
      break;
    case IDC_WINDOW_CLOSE_GROUP:
      qorai::CloseGroup(&*browser_);
      break;
    case IDC_WINDOW_BRING_ALL_TABS:
      qorai::BringAllTabs(&*browser_);
      break;
    case IDC_NEW_SPLIT_VIEW: {
        CHECK(base::FeatureList::IsEnabled(features::kSideBySide));
        chrome::NewSplitTab(base::to_address(browser_),
                            split_tabs::SplitTabCreatedSource::kToolbarButton);
      break;
    }
    case IDC_TILE_TABS: {
        CHECK(base::FeatureList::IsEnabled(features::kSideBySide));
        qorai::SplitTabsWithSideBySide(
            base::to_address(browser_),
            split_tabs::SplitTabCreatedSource::kToolbarButton);
      break;
    }
    case IDC_BREAK_TILE: {
        CHECK(base::FeatureList::IsEnabled(features::kSideBySide));
        qorai::RemoveSplitWithSideBySide(base::to_address(browser_));
      break;
    }
    case IDC_SWAP_SPLIT_VIEW: {
        CHECK(base::FeatureList::IsEnabled(features::kSideBySide));
        qorai::SwapTabsInSplitWithSideBySide(base::to_address(browser_));
      break;
    }
    default:
      LOG(WARNING) << "Received Unimplemented Command: " << id;
      break;
  }

  return true;
}

#if BUILDFLAG(ENABLE_QORAI_VPN)
void QoraiBrowserCommandController::OnPurchasedStateChanged(
    qorai_vpn::mojom::PurchasedState state,
    const std::optional<std::string>& description) {
  UpdateCommandForQoraiVPN();
}
#endif

}  // namespace chrome
