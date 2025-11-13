/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_APPEARANCE_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_APPEARANCE_HANDLER_H_

#include <string>

#include "base/memory/raw_ptr.h"
#include "chrome/browser/ui/webui/settings/settings_page_ui_handler.h"
#include "components/prefs/pref_change_registrar.h"

class Profile;

class QoraiAppearanceHandler : public settings::SettingsPageUIHandler {
 public:
  QoraiAppearanceHandler();
  ~QoraiAppearanceHandler() override;

  QoraiAppearanceHandler(const QoraiAppearanceHandler&) = delete;
  QoraiAppearanceHandler& operator=(const QoraiAppearanceHandler&) = delete;

 private:
  // SettingsPageUIHandler overrides:
  void RegisterMessages() override;
  void OnJavascriptAllowed() override {}
  void OnJavascriptDisallowed() override {}

  void OnPreferenceChanged(const std::string& pref_name);
  void GetNewTabShowsOptionsList(const base::Value::List& args);
  void ShouldShowNewTabDashboardSettings(const base::Value::List& args);

  raw_ptr<Profile> profile_ = nullptr;
  PrefChangeRegistrar profile_state_change_registrar_;
};

#endif  // QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_APPEARANCE_HANDLER_H_
