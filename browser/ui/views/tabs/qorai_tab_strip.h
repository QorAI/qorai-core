/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_TABS_QORAI_TAB_STRIP_H_
#define QORAI_BROWSER_UI_VIEWS_TABS_QORAI_TAB_STRIP_H_

#include <memory>
#include <optional>

#include "base/gtest_prod_util.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/ui/views/tabs/tab_strip.h"

class Tab;
class QoraiTabStrip : public TabStrip {
  METADATA_HEADER(QoraiTabStrip, TabStrip)
 public:
  explicit QoraiTabStrip(std::unique_ptr<TabStripController> controller);
  ~QoraiTabStrip() override;
  QoraiTabStrip(const QoraiTabStrip&) = delete;
  QoraiTabStrip& operator=(const QoraiTabStrip&) = delete;

  bool IsVerticalTabsFloating() const;

  void EnterTabRenameModeAt(int index);

  // TabStrip:
  void ShowHover(Tab* tab, TabStyle::ShowHoverStyle style) override;
  void HideHover(Tab* tab, TabStyle::HideHoverStyle style) override;
  void UpdateHoverCard(Tab* tab, HoverCardUpdateType update_type) override;
  void MaybeStartDrag(
      TabSlotView* source,
      const ui::LocatedEvent& event,
      const ui::ListSelectionModel& original_selection) override;
  void AddedToWidget() override;
  std::optional<int> GetCustomBackgroundId(
      BrowserFrameActiveState active_state) const override;
  void SetCustomTitleForTab(
      Tab* tab,
      const std::optional<std::u16string>& title) override;

 private:
  FRIEND_TEST_ALL_PREFIXES(VerticalTabStripBrowserTest, ScrollBarVisibility);

  void UpdateTabContainer();
  bool ShouldShowVerticalTabs() const;

  TabContainer* GetTabContainerForTesting();

  // TabStrip overrides:
  bool ShouldDrawStrokes() const override;
  void Layout(PassKey) override;

  // Exposed for testing.
  static constexpr float kQoraiMinimumContrastRatioForOutlines = 1.0816f;

  base::WeakPtrFactory<QoraiTabStrip> weak_factory_{this};
};

#endif  // QORAI_BROWSER_UI_VIEWS_TABS_QORAI_TAB_STRIP_H_
