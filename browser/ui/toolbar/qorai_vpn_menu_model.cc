/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/toolbar/qorai_vpn_menu_model.h"

#include "base/feature_list.h"
#include "qorai/app/qorai_command_ids.h"
#include "qorai/components/qorai_vpn/common/qorai_vpn_utils.h"
#include "qorai/components/qorai_vpn/common/features.h"
#include "qorai/components/qorai_vpn/common/pref_names.h"
#include "qorai/grit/qorai_generated_resources.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_commands.h"
#include "components/prefs/pref_service.h"

#if BUILDFLAG(IS_WIN)
#include "qorai/browser/qorai_vpn/win/storage_utils.h"
#endif

QoraiVPNMenuModel::QoraiVPNMenuModel(Browser* browser,
                                     PrefService* profile_prefs)
    : SimpleMenuModel(this), profile_prefs_(profile_prefs), browser_(browser) {
  Build();
}

QoraiVPNMenuModel::~QoraiVPNMenuModel() = default;

void QoraiVPNMenuModel::Build() {
  AddItemWithStringId(IDC_TOGGLE_QORAI_VPN, IDS_QORAI_VPN_MENU);
  AddSeparator(ui::NORMAL_SEPARATOR);
  if (!IsQoraiVPNButtonVisible()) {
    AddItemWithStringId(IDC_TOGGLE_QORAI_VPN_TOOLBAR_BUTTON,
                        IDS_QORAI_VPN_SHOW_VPN_BUTTON_MENU_ITEM);
  }
#if BUILDFLAG(IS_WIN)
  if (!IsTrayIconEnabled()) {
    AddItemWithStringId(IDC_TOGGLE_QORAI_VPN_TRAY_ICON,
                        IDS_QORAI_VPN_SHOW_VPN_TRAY_ICON_MENU_ITEM);
  }
#endif  // BUILDFLAG(IS_WIN)
  AddItemWithStringId(IDC_SEND_QORAI_VPN_FEEDBACK,
                      IDS_QORAI_VPN_SHOW_FEEDBACK_MENU_ITEM);
  AddItemWithStringId(IDC_ABOUT_QORAI_VPN, IDS_QORAI_VPN_ABOUT_VPN_MENU_ITEM);
  AddItemWithStringId(IDC_MANAGE_QORAI_VPN_PLAN,
                      IDS_QORAI_VPN_MANAGE_MY_PLAN_MENU_ITEM);
}

void QoraiVPNMenuModel::ExecuteCommand(int command_id, int event_flags) {
  chrome::ExecuteCommand(browser_, command_id);
}

bool QoraiVPNMenuModel::IsQoraiVPNButtonVisible() const {
  return profile_prefs_->GetBoolean(qorai_vpn::prefs::kQoraiVPNShowButton);
}

#if BUILDFLAG(IS_WIN)
bool QoraiVPNMenuModel::IsTrayIconEnabled() const {
  if (tray_icon_enabled_for_testing_.has_value()) {
    return tray_icon_enabled_for_testing_.value();
  }

  return qorai_vpn::IsVPNTrayIconEnabled();
}
#endif
