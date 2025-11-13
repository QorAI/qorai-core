/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/settings/qorai_appearance_handler.h"

#include "base/check.h"
#include "base/check_op.h"
#include "base/functional/bind.h"
#include "base/metrics/histogram_macros.h"
#include "qorai/browser/new_tab/new_tab_shows_options.h"
#include "qorai/browser/profiles/profile_util.h"
#include "qorai/components/constants/pref_names.h"
#include "qorai/components/ntp_background_images/common/pref_names.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/search/instant_service.h"
#include "chrome/browser/search/instant_service_factory.h"
#include "chrome/common/pref_names.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/web_ui.h"

QoraiAppearanceHandler::QoraiAppearanceHandler() = default;
QoraiAppearanceHandler::~QoraiAppearanceHandler() = default;

// TODO(simonhong): Use separate handler for NTP settings.
void QoraiAppearanceHandler::RegisterMessages() {
  profile_ = Profile::FromWebUI(web_ui());
  profile_state_change_registrar_.Init(profile_->GetPrefs());
  profile_state_change_registrar_.Add(
      kNewTabPageShowsOptions,
      base::BindRepeating(&QoraiAppearanceHandler::OnPreferenceChanged,
                          base::Unretained(this)));
  profile_state_change_registrar_.Add(
      prefs::kHomePageIsNewTabPage,
      base::BindRepeating(&QoraiAppearanceHandler::OnPreferenceChanged,
                          base::Unretained(this)));
  profile_state_change_registrar_.Add(
      prefs::kHomePage,
      base::BindRepeating(&QoraiAppearanceHandler::OnPreferenceChanged,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "getNewTabShowsOptionsList",
      base::BindRepeating(&QoraiAppearanceHandler::GetNewTabShowsOptionsList,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "shouldShowNewTabDashboardSettings",
      base::BindRepeating(
          &QoraiAppearanceHandler::ShouldShowNewTabDashboardSettings,
          base::Unretained(this)));
}

void QoraiAppearanceHandler::OnPreferenceChanged(const std::string& pref_name) {
  if (IsJavascriptAllowed()) {
    if (pref_name == kNewTabPageShowsOptions || pref_name == prefs::kHomePage ||
        pref_name == prefs::kHomePageIsNewTabPage) {
      FireWebUIListener(
          "show-new-tab-dashboard-settings-changed",
          base::Value(qorai::ShouldNewTabShowDashboard(profile_)));
      return;
    }
  }
}

void QoraiAppearanceHandler::GetNewTabShowsOptionsList(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  AllowJavascript();
  ResolveJavascriptCallback(
      args[0], base::Value(qorai::GetNewTabShowsOptionsList(profile_)));
}

void QoraiAppearanceHandler::ShouldShowNewTabDashboardSettings(
    const base::Value::List& args) {
  CHECK_EQ(args.size(), 1U);
  AllowJavascript();
  ResolveJavascriptCallback(
      args[0], base::Value(qorai::ShouldNewTabShowDashboard(profile_)));
}
