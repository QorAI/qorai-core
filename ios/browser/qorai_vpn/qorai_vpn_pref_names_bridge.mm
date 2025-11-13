// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/ios/browser/qorai_vpn/qorai_vpn_pref_names_bridge.h"

#include "base/strings/sys_string_conversions.h"
#include "qorai/components/qorai_vpn/common/buildflags/buildflags.h"

#if BUILDFLAG(ENABLE_QORAI_VPN)
#include "qorai/components/qorai_vpn/common/pref_names.h"
#endif

#if BUILDFLAG(ENABLE_QORAI_VPN)
NSString* const kManagedQoraiVPNDisabledPrefName =
    base::SysUTF8ToNSString(qorai_vpn::prefs::kManagedQoraiVPNDisabled);
#else
NSString* const kManagedQoraiVPNDisabledPrefName = @"";
#endif
