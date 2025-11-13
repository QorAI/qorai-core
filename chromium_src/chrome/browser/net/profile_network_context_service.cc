/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */
static const char* kQoraiCTExcludedHosts[] = {
    // Critical endpoints that shouldn't require SCTs so they always work
    "updates.qoraisoftware.com",
    "updates-cdn.qoraisoftware.com",
    "usage-ping.qorai.com",
    // Test host for manual testing
    "sct-exempted.qoraisoftware.com",
};

#define QORAI_PROFILE_NETWORK_CONTEXT_SERVICE_GET_CT_POLICY \
  for (const auto* host : kQoraiCTExcludedHosts) {          \
    excluded.push_back(host);                               \
  }

#include <chrome/browser/net/profile_network_context_service.cc>
#undef QORAI_PROFILE_NETWORK_CONTEXT_SERVICE_GET_CT_POLICY
