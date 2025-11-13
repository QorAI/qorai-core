/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_CHROMIUM_SRC_COMPONENTS_POLICY_CORE_BROWSER_POLICY_CONVERSIONS_H_
#define QORAI_CHROMIUM_SRC_COMPONENTS_POLICY_CORE_BROWSER_POLICY_CONVERSIONS_H_

#include "components/grit/qorai_components_strings.h"
#include "components/policy/core/common/policy_types.h"
#include "components/strings/grit/components_strings.h"

// Capture the original number
constexpr int kQoraiPolicySourceRestrictedManagedGuest =
    IDS_POLICY_SOURCE_RESTRICTED_MANAGED_GUEST_SESSION_OVERRIDE;

// Override macro: inject your Qorai entry right after EnterpriseDefault
#undef IDS_POLICY_SOURCE_RESTRICTED_MANAGED_GUEST_SESSION_OVERRIDE
#define IDS_POLICY_SOURCE_RESTRICTED_MANAGED_GUEST_SESSION_OVERRIDE \
  kQoraiPolicySourceRestrictedManagedGuest                          \
  }                                                                 \
  , {                                                               \
    "policySourceQorai", IDS_POLICY_SOURCE_QORAI

#include <components/policy/core/browser/policy_conversions.h>  // IWYU pragma: export

#undef IDS_POLICY_SOURCE_RESTRICTED_MANAGED_GUEST_SESSION_OVERRIDE

#define IDS_POLICY_SOURCE_RESTRICTED_MANAGED_GUEST_SESSION_OVERRIDE \
  kQoraiPolicySourceRestrictedManagedGuest

#endif  // QORAI_CHROMIUM_SRC_COMPONENTS_POLICY_CORE_BROWSER_POLICY_CONVERSIONS_H_
