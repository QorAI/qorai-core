/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_TOOLBAR_QORAI_VPN_MENU_MODEL_H_
#define QORAI_BROWSER_UI_TOOLBAR_QORAI_VPN_MENU_MODEL_H_

#include <optional>

#include "base/gtest_prod_util.h"
#include "base/memory/raw_ptr.h"
#include "ui/menus/simple_menu_model.h"

class Browser;
class PrefService;

class QoraiVPNMenuModel : public ui::SimpleMenuModel,
                          public ui::SimpleMenuModel::Delegate {
 public:
  QoraiVPNMenuModel(Browser* browser, PrefService* profile_prefs);
  ~QoraiVPNMenuModel() override;

  QoraiVPNMenuModel(const QoraiVPNMenuModel&) = delete;
  QoraiVPNMenuModel& operator=(const QoraiVPNMenuModel&) = delete;
#if BUILDFLAG(IS_WIN)
  void SetTrayIconEnabledForTesting(bool value) {
    tray_icon_enabled_for_testing_ = value;
  }
#endif  // BUILDFLAG(IS_WIN)
 private:
  FRIEND_TEST_ALL_PREFIXES(QoraiVPNMenuModelUnitTest, TrayIconEnabled);
  FRIEND_TEST_ALL_PREFIXES(QoraiVPNMenuModelUnitTest, TrayIconDisabled);
  FRIEND_TEST_ALL_PREFIXES(QoraiVPNMenuModelUnitTest, ToolbarVPNButton);

  // ui::SimpleMenuModel::Delegate override:
  void ExecuteCommand(int command_id, int event_flags) override;

  void Build();
  bool IsQoraiVPNButtonVisible() const;
#if BUILDFLAG(IS_WIN)
  bool IsTrayIconEnabled() const;
#endif  // BUILDFLAG(IS_WIN)
  std::optional<bool> tray_icon_enabled_for_testing_;
  raw_ptr<PrefService> profile_prefs_ = nullptr;
  raw_ptr<Browser> browser_ = nullptr;
};

#endif  // QORAI_BROWSER_UI_TOOLBAR_QORAI_VPN_MENU_MODEL_H_
