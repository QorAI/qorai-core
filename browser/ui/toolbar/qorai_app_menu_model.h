/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_TOOLBAR_QORAI_APP_MENU_MODEL_H_
#define QORAI_BROWSER_UI_TOOLBAR_QORAI_APP_MENU_MODEL_H_

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/gtest_prod_util.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"
#include "chrome/browser/ui/toolbar/app_menu_model.h"
#include "ui/menus/simple_menu_model.h"

#if defined(TOOLKIT_VIEWS)
#include "qorai/components/sidebar/browser/sidebar_service.h"
#endif  // defined(TOOLKIT_VIEWS)

namespace ui {
class ButtonMenuItemModel;
}

class QoraiAppMenuModel : public AppMenuModel {
 public:
  QoraiAppMenuModel(ui::AcceleratorProvider* provider,
                    Browser* browser,
                    AppMenuIconController* app_menu_icon_controller = nullptr,
                    AlertMenuItem alert_item = AlertMenuItem::kNone);
  ~QoraiAppMenuModel() override;

  QoraiAppMenuModel(const QoraiAppMenuModel&) = delete;
  QoraiAppMenuModel& operator=(const QoraiAppMenuModel&) = delete;

#if defined(TOOLKIT_VIEWS)
  static sidebar::SidebarService::ShowSidebarOption
  ConvertIDCToSidebarShowOptions(int id);
#endif  // defined(TOOLKIT_VIEWS)

 private:
  FRIEND_TEST_ALL_PREFIXES(QoraiAppMenuModelBrowserTest, QoraiIpfsMenuTest);
  friend class QoraiAppMenuModelBrowserTest;

  // AppMenuModel overrides:
  void Build() override;
  void ExecuteCommand(int id, int event_flags) override;
  bool IsCommandIdEnabled(int id) const override;

  std::optional<size_t> GetProperItemIndex(std::vector<int> commands_to_check,
                                           bool insert_next) const;

  void BuildTabsAndWindowsSection();

  // Qora(not yet added), Wallet, VPN and IPFS.
  void BuildQoraiProductsSection();
  size_t GetNextIndexOfQoraiProductsSection() const;

  // History, bookmarks, downloads and extensions.
  void BuildBrowserSection();

  // Insert profile, sidebar, sync and cast entries into existing more tools
  // sub menu.
  void BuildMoreToolsSubMenu();

  // About qorai, help center and report broken site items.
  void BuildHelpSubMenu();

  // We relocate some upstream items. Need to remove them before adding them
  // to another location.
  void RemoveUpstreamMenus();

#if defined(TOOLKIT_VIEWS)
  std::unique_ptr<ui::ButtonMenuItemModel> sidebar_show_option_model_;
#endif  // defined(TOOLKIT_VIEWS)
};

#endif  // QORAI_BROWSER_UI_TOOLBAR_QORAI_APP_MENU_MODEL_H_
