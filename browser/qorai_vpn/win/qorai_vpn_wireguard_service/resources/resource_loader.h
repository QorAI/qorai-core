/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_SERVICE_RESOURCES_RESOURCE_LOADER_H_
#define QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_SERVICE_RESOURCES_RESOURCE_LOADER_H_

#include <string>

namespace base {
class FilePath;
}  // namespace base

namespace qorai_vpn {

void LoadLocaleResources();

base::FilePath FindPakFilePath(const base::FilePath& assets_path,
                               const std::string& locale);

}  //  namespace qorai_vpn

#endif  // QORAI_BROWSER_QORAI_VPN_WIN_QORAI_VPN_WIREGUARD_SERVICE_RESOURCES_RESOURCE_LOADER_H_
