// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_TOR_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_TOR_HANDLER_H_

#include <memory>

#include "base/values.h"
#include "chrome/browser/ui/webui/settings/settings_page_ui_handler.h"
#include "components/prefs/pref_change_registrar.h"

class QoraiTorHandler : public settings::SettingsPageUIHandler {
 public:
  QoraiTorHandler();
  QoraiTorHandler(const QoraiTorHandler&) = delete;
  QoraiTorHandler& operator=(const QoraiTorHandler&) = delete;
  ~QoraiTorHandler() override;

 private:
  // SettingsPageUIHandler overrides:
  void RegisterMessages() override;
  void OnJavascriptAllowed() override {}
  void OnJavascriptDisallowed() override {}

  void GetBridgesConfig(const base::Value::List& args);
  void SetBridgesConfig(const base::Value::List& args);
  void RequestBridgesCaptcha(const base::Value::List& args);
  void ResolveBridgesCaptcha(const base::Value::List& args);

  void SendResultToJavascript(bool reset_request,
                              const base::Value& callback_id,
                              const base::Value& response);

  void SetTorEnabled(const base::Value::List& args);
  void IsTorEnabled(const base::Value::List& args);
  void IsTorManaged(const base::Value::List& args);
  void OnTorEnabledChanged();

  PrefChangeRegistrar local_state_change_registrar_;

  std::unique_ptr<class BridgeRequest> request_;
};

#endif  // QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_TOR_HANDLER_H_
