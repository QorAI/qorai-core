/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_CHROME_COMMON_PREF_NAMES_H_
#define QORAI_CHROMIUM_SRC_CHROME_COMMON_PREF_NAMES_H_

#include "build/build_config.h"

namespace prefs {
// Used by QoraiVpnDnsObserverService to set cloudflare server url when
// QoraiVPN is connected, otherwise this pref is empty. Final decision
// about whether or not to override actual DNS state will be made in
// stub_resolver_config_reader.
inline constexpr char kQoraiVpnDnsConfig[] = "qorai.qorai_vpn.dns_config";
}  // namespace prefs

#include <chrome/common/pref_names.h>  // IWYU pragma: export

#endif  // QORAI_CHROMIUM_SRC_CHROME_COMMON_PREF_NAMES_H_
