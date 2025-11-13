/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_VPN_COMMON_FEATURES_H_
#define QORAI_COMPONENTS_QORAI_VPN_COMMON_FEATURES_H_

#include "base/feature_list.h"
#include "build/build_config.h"

namespace qorai_vpn {
namespace features {

BASE_DECLARE_FEATURE(kQoraiVPN);
BASE_DECLARE_FEATURE(kQoraiVPNLinkSubscriptionAndroidUI);
#if BUILDFLAG(IS_WIN)
BASE_DECLARE_FEATURE(kQoraiVPNDnsProtection);
BASE_DECLARE_FEATURE(kQoraiVPNUseWireguardService);
#endif
#if BUILDFLAG(IS_MAC)
BASE_DECLARE_FEATURE(kQoraiVPNEnableWireguardForOSX);
#endif
}  // namespace features
}  // namespace qorai_vpn

#endif  // QORAI_COMPONENTS_QORAI_VPN_COMMON_FEATURES_H_
