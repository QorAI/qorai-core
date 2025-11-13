/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_SERVICE_DETAILS_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_SERVICE_DETAILS_H_

#include <guiddef.h>
#include <string>

#include "base/files/file_path.h"
#include "base/version.h"

namespace qorai_vpn {
const CLSID& GetQorAIVpnWireguardServiceClsid();
const IID& GetQorAIVpnWireguardServiceIid();
std::wstring GetQorAIVpnWireguardTunnelServiceName();
std::wstring GetQorAIVpnWireguardServiceName();
std::wstring GetQorAIVpnWireguardServiceDisplayName();
std::wstring GetQorAIVpnWireguardServiceDescription();
base::FilePath GetQorAIVPNWireguardServiceExecutablePath(
    const base::FilePath& root_dir);
}  // namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_SERVICE_DETAILS_H_
