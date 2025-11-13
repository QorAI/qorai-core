/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "components/crash/core/app/crashpad.h"

#if BUILDFLAG(IS_WIN)
namespace {
// Split into two places to avoid patching:
// NOLINTNEXTLINE
// components\qorai_vpn\browser\connection\win\qorai_vpn_helper\qorai_vpn_helper_crash_reporter_client.cc
// Need keep it in sync
constexpr char kQoraiVPNHelperProcessType[] = "qorai-vpn-helper";

// Split into two places to avoid patching:
// NOLINTNEXTLINE
// components\qorai_vpn\browser\connection\wireguard\win\qorai_vpn_wireguard_service\qorai_wireguard_service_crash_reporter_client.cc
// Need keep it in sync
constexpr char kQoraiWireguardProcessType[] = "qorai-vpn-wireguard-service";
}  // namespace

#define QORAI_INITIALIZE_CRASHPAD_IMPL_PROCESS_TYPE \
  process_type == kQoraiVPNHelperProcessType ||     \
      process_type == kQoraiWireguardProcessType ||
#endif

#include <components/crash/core/app/crashpad.cc>
#if BUILDFLAG(IS_WIN)
#undef QORAI_INITIALIZE_CRASHPAD_IMPL_PROCESS_TYPE
#endif
