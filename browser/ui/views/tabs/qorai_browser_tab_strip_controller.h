/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_VIEWS_TABS_QORAI_BROWSER_TAB_STRIP_CONTROLLER_H_
#define QORAI_BROWSER_UI_VIEWS_TABS_QORAI_BROWSER_TAB_STRIP_CONTROLLER_H_

#include <memory>
#include <optional>

#include "chrome/browser/ui/views/tabs/browser_tab_strip_controller.h"

class QoraiTabContextMenuContents;

class QoraiBrowserTabStripController : public BrowserTabStripController {
 public:
  QoraiBrowserTabStripController(TabStripModel* model,
                                 BrowserView* browser_view,
                                 std::unique_ptr<TabMenuModelFactory>
                                     menu_model_factory_override = nullptr);
  QoraiBrowserTabStripController(const QoraiBrowserTabStripController&) =
      delete;
  QoraiBrowserTabStripController& operator=(
      const QoraiBrowserTabStripController&) = delete;
  ~QoraiBrowserTabStripController() override;

  const std::optional<int> GetModelIndexOf(Tab* tab);

  // Enters rename mode for the tab at the given index. This only affects UI
  // side.
  void EnterTabRenameModeAt(int index);

  // Sets the custom title for the tab at the specified index.
  void SetCustomTitleForTab(int index,
                            const std::optional<std::u16string>& title);

  // BrowserTabStripController overrides:
  void ShowContextMenuForTab(Tab* tab,
                             const gfx::Point& p,
                             ui::mojom::MenuSourceType source_type) override;
  void ExecuteCommandForTab(TabStripModel::ContextMenuCommand command_id,
                            const Tab* tab) override;

 private:
  // If non-NULL it means we're showing a menu for the tab.
  std::unique_ptr<QoraiTabContextMenuContents> context_menu_contents_;
};

#endif  // QORAI_BROWSER_UI_VIEWS_TABS_QORAI_BROWSER_TAB_STRIP_CONTROLLER_H_
