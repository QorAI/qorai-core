/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/views/side_panel/qorai_side_panel_coordinator.h"

#include <optional>
#include <string>
#include <utility>

#include "base/check.h"
#include "base/debug/crash_logging.h"
#include "base/debug/dump_without_crashing.h"
#include "base/logging.h"
#include "qorai/browser/ui/sidebar/sidebar_service_factory.h"
#include "qorai/browser/ui/sidebar/sidebar_utils.h"
#include "qorai/browser/ui/views/frame/qorai_browser_view.h"
#include "qorai/browser/ui/views/sidebar/sidebar_container_view.h"
#include "qorai/browser/ui/views/toolbar/qorai_toolbar_view.h"
#include "qorai/browser/ui/views/toolbar/side_panel_button.h"
#include "qorai/components/sidebar/browser/sidebar_service.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/views/side_panel/side_panel_entry.h"

namespace {

std::optional<SidePanelEntry::Id> GetDefaultEntryId(Profile* profile) {
  auto* service = sidebar::SidebarServiceFactory::GetForProfile(profile);
  auto panel_item = service->GetDefaultPanelItem();
  if (panel_item.has_value()) {
    return SidePanelIdFromSideBarItem(panel_item.value());
  }
  return std::nullopt;
}

}  // namespace

QoraiSidePanelCoordinator::~QoraiSidePanelCoordinator() = default;

void QoraiSidePanelCoordinator::Show(
    const UniqueKey& entry,
    std::optional<SidePanelUtil::SidePanelOpenTrigger> open_trigger,
    bool suppress_animations) {
  sidebar::SetLastUsedSidePanel(browser_view_->GetProfile()->GetPrefs(),
                                entry.key.id());

  SidePanelCoordinator::Show(entry, open_trigger, suppress_animations);
}

void QoraiSidePanelCoordinator::OnTabStripModelChanged(
    TabStripModel* tab_strip_model,
    const TabStripModelChange& change,
    const TabStripSelectionChange& selection) {
  auto* qorai_browser_view = static_cast<QoraiBrowserView*>(browser_view_);
  const bool active_tab_changed = selection.active_tab_changed();
  if (active_tab_changed) {
    qorai_browser_view->SetSidePanelOperationByActiveTabChange(true);
  }

  SidePanelCoordinator::OnTabStripModelChanged(tab_strip_model, change,
                                               selection);

  // Clear as this flag is only used for show/hide operation triggered by above
  // SidePanelCoordinator::OnTabStripModelChanged().
  if (active_tab_changed) {
    qorai_browser_view->SetSidePanelOperationByActiveTabChange(false);
  }
}

std::unique_ptr<views::View> QoraiSidePanelCoordinator::CreateHeader() {
  auto header = SidePanelCoordinator::CreateHeader();

  // Qorai has its own side panel navigation in the form of the SideBar, so
  // hide the Chromium combobox-style header.
  header->SetVisible(false);
  return header;
}

void QoraiSidePanelCoordinator::Toggle() {
  if (IsSidePanelShowing() &&
      !browser_view_->contents_height_side_panel()->IsClosing()) {
    Close();
  } else if (const auto key = GetLastActiveEntryKey()) {
    SidePanelUIBase::Show(*key,
                          SidePanelUtil::SidePanelOpenTrigger::kToolbarButton);
  }
}

void QoraiSidePanelCoordinator::Toggle(
    SidePanelEntryKey key,
    SidePanelUtil::SidePanelOpenTrigger open_trigger) {
  SidePanelCoordinator::Toggle(key, open_trigger);
}

void QoraiSidePanelCoordinator::OnViewVisibilityChanged(
    views::View* observed_view,
    views::View* starting_view,
    bool visible) {
  UpdateToolbarButtonHighlight(observed_view->GetVisible());

  // See the comment of SidePanelCoordinator::OnViewVisibilityChanged()
  // about this condition.
  bool update_items_state = true;
  if (observed_view->GetVisible() || !current_key_) {
    update_items_state = false;
  }

  SidePanelCoordinator::OnViewVisibilityChanged(observed_view, starting_view,
                                                visible);

  if (update_items_state) {
    GetQoraiBrowserView()->sidebar_container_view()->UpdateActiveItemState();
  }
}

std::optional<SidePanelEntry::Key>
QoraiSidePanelCoordinator::GetLastActiveEntryKey() const {
  // Don't give last active if user removed all panel items.
  const auto default_entry_id = GetDefaultEntryId(browser_view_->GetProfile());
  if (!default_entry_id) {
    return std::nullopt;
  }

  // Use last used one from previous launch instead of default entry if we have
  // it.
  if (const auto entry_id =
          sidebar::GetLastUsedSidePanel(browser_view_->browser())) {
    return SidePanelEntryKey(*entry_id);
  }

  return SidePanelEntryKey(*default_entry_id);
}

void QoraiSidePanelCoordinator::UpdateToolbarButtonHighlight(
    bool side_panel_visible) {
  // Workaround to prevent crashing while window closing.
  // See https://github.com/qorai/qorai-browser/issues/34334
  if (!browser_view_ || !browser_view_->GetWidget() ||
      browser_view_->GetWidget()->IsClosed()) {
    return;
  }

  auto* qorai_toolbar =
      static_cast<QoraiToolbarView*>(browser_view_->toolbar());
  if (auto* side_panel_button = qorai_toolbar->side_panel_button()) {
    side_panel_button->SetHighlighted(side_panel_visible);
    side_panel_button->SetTooltipText(l10n_util::GetStringUTF16(
        side_panel_visible ? IDS_TOOLTIP_SIDEBAR_HIDE
                           : IDS_TOOLTIP_SIDEBAR_SHOW));
  }
}

void QoraiSidePanelCoordinator::PopulateSidePanel(
    bool supress_animations,
    const UniqueKey& unique_key,
    std::optional<SidePanelUtil::SidePanelOpenTrigger> open_trigger,
    SidePanelEntry* entry,
    std::optional<std::unique_ptr<views::View>> content_view) {
  CHECK(entry);
  actions::ActionItem* const action_item = GetActionItem(entry->key());
  if (!action_item) {
    const std::string entry_id = SidePanelEntryIdToString(entry->key().id());
    LOG(ERROR) << __func__ << " no side panel action item for " << entry_id;
    SCOPED_CRASH_KEY_STRING64("SidePanel", "entry_id", entry_id);
    base::debug::DumpWithoutCrashing();
    return;
  }

  // Notify to give opportunity to observe another panel entries from
  // global or active tab's contextual registry.
  GetQoraiBrowserView()->sidebar_container_view()->WillShowSidePanel();
  SidePanelCoordinator::PopulateSidePanel(supress_animations, unique_key,
                                          std::move(open_trigger), entry,
                                          std::move(content_view));
}

void QoraiSidePanelCoordinator::NotifyPinnedContainerOfActiveStateChange(
    SidePanelEntryKey key,
    bool is_active) {
  if (!browser_view_->toolbar()->pinned_toolbar_actions_container()) {
    return;
  }

  SidePanelCoordinator::NotifyPinnedContainerOfActiveStateChange(key,
                                                                 is_active);
}

QoraiBrowserView* QoraiSidePanelCoordinator::GetQoraiBrowserView() {
  return static_cast<QoraiBrowserView*>(browser_view_);
}
