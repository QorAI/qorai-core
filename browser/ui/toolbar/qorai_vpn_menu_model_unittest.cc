/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/toolbar/qorai_vpn_menu_model.h"

#include <memory>

#include "base/test/scoped_feature_list.h"
#include "qorai/app/qorai_command_ids.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#include "qorai/components/qorai_vpn/common/features.h"
#include "qorai/components/qorai_vpn/common/pref_names.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "chrome/browser/browser_process.h"
#include "chrome/test/base/testing_browser_process.h"
#include "components/prefs/pref_service.h"
#include "components/prefs/testing_pref_service.h"
#include "components/sync_preferences/testing_pref_service_syncable.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/menus/simple_menu_model.h"

class QoraiVPNMenuModelUnitTest : public testing::Test {
 public:
  QoraiVPNMenuModelUnitTest() = default;
  ~QoraiVPNMenuModelUnitTest() override = default;

  PrefService* prefs() { return &prefs_; }

  void SetUp() override {
    qorai_vpn::RegisterProfilePrefs(prefs_.registry());
  }

  TestingPrefServiceSimple* local_state() {
    return TestingBrowserProcess::GetGlobal()->GetTestingLocalState();
  }

 private:
  sync_preferences::TestingPrefServiceSyncable prefs_;
};

#if BUILDFLAG(IS_WIN)
TEST_F(QoraiVPNMenuModelUnitTest, TrayIconEnabled) {
  local_state()->SetBoolean(qorai_vpn::prefs::kQoraiVPNWireguardEnabled, true);

  QoraiVPNMenuModel menu_model(nullptr, prefs());

  // Cases with Enabled value.
  menu_model.SetTrayIconEnabledForTesting(true);
  prefs()->SetBoolean(qorai_vpn::prefs::kQoraiVPNShowButton, true);
  EXPECT_TRUE(menu_model.IsTrayIconEnabled());
  menu_model.Clear();
  EXPECT_EQ(menu_model.GetItemCount(), 0u);
  menu_model.Build();
  EXPECT_NE(menu_model.GetItemCount(), 0u);
  {
    // Don't show toggle menu when tray icon is visible.
    EXPECT_FALSE(
        menu_model.GetIndexOfCommandId(IDC_TOGGLE_QORAI_VPN_TRAY_ICON));
  }

  // Wireguard protocol disbled in the setting.
  EXPECT_TRUE(menu_model.IsTrayIconEnabled());
  menu_model.Clear();
  EXPECT_EQ(menu_model.GetItemCount(), 0u);
  menu_model.Build();
  EXPECT_NE(menu_model.GetItemCount(), 0u);
  {
    // Still toggle menu is hidden.
    EXPECT_FALSE(
        menu_model.GetIndexOfCommandId(IDC_TOGGLE_QORAI_VPN_TRAY_ICON));
  }

  // Cases with Disabled value.
  menu_model.SetTrayIconEnabledForTesting(false);
  prefs()->SetBoolean(qorai_vpn::prefs::kQoraiVPNShowButton, false);
  EXPECT_FALSE(menu_model.IsTrayIconEnabled());
  menu_model.Clear();
  EXPECT_EQ(menu_model.GetItemCount(), 0u);
  menu_model.Build();
  EXPECT_NE(menu_model.GetItemCount(), 0u);
  {
    auto tray_index =
        menu_model.GetIndexOfCommandId(IDC_TOGGLE_QORAI_VPN_TRAY_ICON);
    EXPECT_TRUE(tray_index);
    EXPECT_EQ(
        menu_model.GetLabelAt(tray_index.value()),
        l10n_util::GetStringUTF16(IDS_QORAI_VPN_SHOW_VPN_TRAY_ICON_MENU_ITEM));
  }
}
#endif  // BUILDFLAG(IS_WIN)

TEST_F(QoraiVPNMenuModelUnitTest, ToolbarVPNButton) {
  QoraiVPNMenuModel menu_model(nullptr, prefs());

  // Cases with Enabled value.
  prefs()->SetBoolean(qorai_vpn::prefs::kQoraiVPNShowButton, true);

  EXPECT_TRUE(menu_model.IsQoraiVPNButtonVisible());
  menu_model.Clear();
  EXPECT_EQ(menu_model.GetItemCount(), 0u);
  menu_model.Build();
  EXPECT_NE(menu_model.GetItemCount(), 0u);
  {
    // Don't show toggle menu when button is visible.
    EXPECT_FALSE(
        menu_model.GetIndexOfCommandId(IDC_TOGGLE_QORAI_VPN_TOOLBAR_BUTTON));
  }

  // Cases with Disabled value.
  prefs()->SetBoolean(qorai_vpn::prefs::kQoraiVPNShowButton, false);
  EXPECT_FALSE(menu_model.IsQoraiVPNButtonVisible());
  menu_model.Clear();
  EXPECT_EQ(menu_model.GetItemCount(), 0u);
  menu_model.Build();
  EXPECT_NE(menu_model.GetItemCount(), 0u);
  {
    auto toolbar_index =
        menu_model.GetIndexOfCommandId(IDC_TOGGLE_QORAI_VPN_TOOLBAR_BUTTON);
    EXPECT_TRUE(toolbar_index);
    EXPECT_EQ(
        menu_model.GetLabelAt(toolbar_index.value()),
        l10n_util::GetStringUTF16(IDS_QORAI_VPN_SHOW_VPN_BUTTON_MENU_ITEM));
  }
}
