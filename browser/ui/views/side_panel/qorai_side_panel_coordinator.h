/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_SIDE_PANEL_QORAI_SIDE_PANEL_COORDINATOR_H_
#define QORAI_BROWSER_UI_VIEWS_SIDE_PANEL_QORAI_SIDE_PANEL_COORDINATOR_H_

#include <memory>
#include <optional>

#include "chrome/browser/ui/views/side_panel/side_panel_coordinator.h"

class QoraiBrowserView;

class QoraiSidePanelCoordinator : public SidePanelCoordinator {
 public:
  using SidePanelCoordinator::SidePanelCoordinator;
  ~QoraiSidePanelCoordinator() override;

  // SidePanelUI overrides:
  void Toggle() override;
  void Toggle(SidePanelEntryKey key,
              SidePanelUtil::SidePanelOpenTrigger open_trigger) override;

  // SidePanelUIBase overrides:
  void Show(const UniqueKey& entry,
            std::optional<SidePanelUtil::SidePanelOpenTrigger> open_trigger,
            bool suppress_animations) override;
  void OnTabStripModelChanged(
      TabStripModel* tab_strip_model,
      const TabStripModelChange& change,
      const TabStripSelectionChange& selection) override;
  void PopulateSidePanel(
      bool supress_animations,
      const UniqueKey& unique_key,
      std::optional<SidePanelUtil::SidePanelOpenTrigger> open_trigger,
      SidePanelEntry* entry,
      std::optional<std::unique_ptr<views::View>> content_view) override;

  // views::ViewObserver:
  void OnViewVisibilityChanged(views::View* observed_view,
                               views::View* starting_view,
                               bool visible) override;

  // SidePanelCoordinator overrides:
  std::unique_ptr<views::View> CreateHeader() override;
  void NotifyPinnedContainerOfActiveStateChange(SidePanelEntryKey key,
                                                bool is_active) override;

 private:
  // Returns the last active entry or the default entry if no last active
  // entry exists.
  std::optional<SidePanelEntry::Key> GetLastActiveEntryKey() const;
  void UpdateToolbarButtonHighlight(bool side_panel_visible);
  QoraiBrowserView* GetQoraiBrowserView();
};

#endif  // QORAI_BROWSER_UI_VIEWS_SIDE_PANEL_QORAI_SIDE_PANEL_COORDINATOR_H_
