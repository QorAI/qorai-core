/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_NET_BASE_FEATURES_H_
#define QORAI_CHROMIUM_SRC_NET_BASE_FEATURES_H_

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"
#include "qorai/net/dns/secure_dns_endpoints.h"
#include "net/base/net_export.h"

namespace net {
namespace features {

NET_EXPORT BASE_DECLARE_FEATURE(kQoraiEphemeralStorage);
NET_EXPORT BASE_DECLARE_FEATURE(kQoraiEphemeralStorageKeepAlive);
NET_EXPORT extern const base::FeatureParam<int>
    kQoraiEphemeralStorageKeepAliveTimeInSeconds;
NET_EXPORT BASE_DECLARE_FEATURE(kQoraiFirstPartyEphemeralStorage);
NET_EXPORT BASE_DECLARE_FEATURE(kQoraiHttpsByDefault);
NET_EXPORT BASE_DECLARE_FEATURE(kQoraiFallbackDoHProvider);
NET_EXPORT extern const base::FeatureParam<DohFallbackEndpointType>
    kQoraiFallbackDoHProviderEndpoint;
NET_EXPORT BASE_DECLARE_FEATURE(kQoraiPartitionHSTS);
NET_EXPORT BASE_DECLARE_FEATURE(kQoraiTorWindowsHttpsOnly);
NET_EXPORT BASE_DECLARE_FEATURE(kQoraiForgetFirstPartyStorage);
NET_EXPORT BASE_DECLARE_FEATURE(kQoraiProvisionalTLDEphemeralLifetime);
NET_EXPORT extern const base::FeatureParam<int>
    kQoraiForgetFirstPartyStorageStartupCleanupDelayInSeconds;
NET_EXPORT extern const base::FeatureParam<bool>
    kQoraiForgetFirstPartyStorageByDefault;

}  // namespace features
}  // namespace net

#include <net/base/features.h>  // IWYU pragma: export

#endif  // QORAI_CHROMIUM_SRC_NET_BASE_FEATURES_H_
