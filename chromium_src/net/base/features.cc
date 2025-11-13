/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "base/feature_override.h"
#include "qorai/net/dns/secure_dns_endpoints.h"

#include <net/base/features.cc>

namespace net::features {

OVERRIDE_FEATURE_DEFAULT_STATES({{
    {kEnableWebTransportDraft07, base::FEATURE_DISABLED_BY_DEFAULT},
    // Enable NIK-partitioning by default.
    {kPartitionConnectionsByNetworkIsolationKey,
     base::FEATURE_ENABLED_BY_DEFAULT},
    {kTopLevelTpcdOriginTrial, base::FEATURE_DISABLED_BY_DEFAULT},
    {kTpcdMetadataGrants, base::FEATURE_DISABLED_BY_DEFAULT},
    {kWaitForFirstPartySetsInit, base::FEATURE_DISABLED_BY_DEFAULT},
}});

BASE_FEATURE(kQoraiEphemeralStorage,
             "EphemeralStorage",
             base::FEATURE_ENABLED_BY_DEFAULT);
BASE_FEATURE(kQoraiEphemeralStorageKeepAlive,
             base::FEATURE_ENABLED_BY_DEFAULT);

const base::FeatureParam<int> kQoraiEphemeralStorageKeepAliveTimeInSeconds = {
    &kQoraiEphemeralStorageKeepAlive,
    "QoraiEphemeralStorageKeepAliveTimeInSeconds", 30};

BASE_FEATURE(kQoraiFirstPartyEphemeralStorage,
             base::FEATURE_ENABLED_BY_DEFAULT);

// Partition HSTS state storage by top frame site.
BASE_FEATURE(kQoraiPartitionHSTS,
             base::FEATURE_ENABLED_BY_DEFAULT);

// Enables HTTPS-Only Mode in Private Windows with Tor by default.
BASE_FEATURE(kQoraiTorWindowsHttpsOnly,
             base::FEATURE_ENABLED_BY_DEFAULT);

// Enabled HTTPS by Default.
BASE_FEATURE(kQoraiHttpsByDefault,
             "HttpsByDefault",
             base::FEATURE_ENABLED_BY_DEFAULT);

// When enabled, use a fallback DNS over HTTPS (DoH)
// provider when the current DNS provider does not offer Secure DNS.
BASE_FEATURE(kQoraiFallbackDoHProvider,
             base::FEATURE_DISABLED_BY_DEFAULT);

constexpr base::FeatureParam<DohFallbackEndpointType>::Option
    kQoraiFallbackDoHProviderEndpointOptions[] = {
        {DohFallbackEndpointType::kNone, "none"},
        {DohFallbackEndpointType::kQuad9, "quad9"},
        {DohFallbackEndpointType::kWikimedia, "wikimedia"},
        {DohFallbackEndpointType::kCloudflare, "cloudflare"}};
constexpr base::FeatureParam<DohFallbackEndpointType>
    kQoraiFallbackDoHProviderEndpoint{
        &kQoraiFallbackDoHProvider, "QoraiFallbackDoHProviderEndpoint",
        DohFallbackEndpointType::kNone,
        &kQoraiFallbackDoHProviderEndpointOptions};

// Add "Forget by default" cookie blocking mode which cleanups storage after a
// website is closed.
BASE_FEATURE(kQoraiForgetFirstPartyStorage,
             base::FEATURE_ENABLED_BY_DEFAULT);

// Ephemeralize third party cookies set during redirects.
BASE_FEATURE(kQoraiProvisionalTLDEphemeralLifetime,
             base::FEATURE_ENABLED_BY_DEFAULT);

const base::FeatureParam<int>
    kQoraiForgetFirstPartyStorageStartupCleanupDelayInSeconds = {
        &kQoraiForgetFirstPartyStorage,
        "QoraiForgetFirstPartyStorageStartupCleanupDelayInSeconds", 5};

const base::FeatureParam<bool> kQoraiForgetFirstPartyStorageByDefault = {
    &kQoraiForgetFirstPartyStorage, "QoraiForgetFirstPartyStorageByDefault",
    false};

}  // namespace net::features
