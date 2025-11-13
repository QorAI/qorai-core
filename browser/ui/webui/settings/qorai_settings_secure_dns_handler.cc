/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/settings/qorai_settings_secure_dns_handler.h"

#include "base/feature_list.h"
#include "qorai/components/qorai_vpn/common/features.h"
#include "chrome/browser/browser_process.h"
#include "chrome/common/pref_names.h"
#include "components/prefs/pref_service.h"

namespace settings {

QoraiSecureDnsHandler::QoraiSecureDnsHandler() = default;
QoraiSecureDnsHandler::~QoraiSecureDnsHandler() = default;

void QoraiSecureDnsHandler::OnJavascriptAllowed() {
  SecureDnsHandler::OnJavascriptAllowed();
  pref_registrar_.Init(g_browser_process->local_state());
  if (base::FeatureList::IsEnabled(
          qorai_vpn::features::kQoraiVPNDnsProtection)) {
    pref_registrar_.Add(
        prefs::kQoraiVpnDnsConfig,
        base::BindRepeating(
            &QoraiSecureDnsHandler::SendSecureDnsSettingUpdatesToJavascript,
            base::Unretained(this)));
  }
}

void QoraiSecureDnsHandler::OnJavascriptDisallowed() {
  SecureDnsHandler::OnJavascriptDisallowed();
  pref_registrar_.RemoveAll();
}

}  // namespace settings
