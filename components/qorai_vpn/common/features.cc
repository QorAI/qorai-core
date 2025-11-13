/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_vpn/common/features.h"

#include "base/feature_list.h"
#include "build/build_config.h"

namespace qorai_vpn {

namespace features {

BASE_FEATURE(kQoraiVPN,
#if !BUILDFLAG(IS_LINUX)
             base::FEATURE_ENABLED_BY_DEFAULT
#else
             base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kQoraiVPNLinkSubscriptionAndroidUI,
             base::FEATURE_ENABLED_BY_DEFAULT);

#if BUILDFLAG(IS_WIN)
BASE_FEATURE(kQoraiVPNDnsProtection,
             base::FEATURE_ENABLED_BY_DEFAULT);
BASE_FEATURE(kQoraiVPNUseWireguardService,
             base::FEATURE_ENABLED_BY_DEFAULT);
#endif
#if BUILDFLAG(IS_MAC)
BASE_FEATURE(kQoraiVPNEnableWireguardForOSX,
             base::FEATURE_DISABLED_BY_DEFAULT);
#endif
}  // namespace features

}  // namespace qorai_vpn
