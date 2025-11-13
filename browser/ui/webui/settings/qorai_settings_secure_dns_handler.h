/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_SETTINGS_SECURE_DNS_HANDLER_H_
#define QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_SETTINGS_SECURE_DNS_HANDLER_H_

#include "chrome/browser/ui/webui/settings/settings_secure_dns_handler.h"
#include "components/prefs/pref_change_registrar.h"

namespace settings {

class QoraiSecureDnsHandler : public SecureDnsHandler {
 public:
  QoraiSecureDnsHandler();
  ~QoraiSecureDnsHandler() override;

  void OnJavascriptAllowed() override;
  void OnJavascriptDisallowed() override;

 private:
  PrefChangeRegistrar pref_registrar_;
};

}  // namespace settings

#endif  // QORAI_BROWSER_UI_WEBUI_SETTINGS_QORAI_SETTINGS_SECURE_DNS_HANDLER_H_
