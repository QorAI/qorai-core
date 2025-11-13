/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/permission_rules_base.h"

#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/command_line_permission_rule.h"
#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/confirmation_tokens_permission_rule.h"
#include "qorai/components/qorai_ads/core/internal/serving/permission_rules/issuers_permission_rule.h"

namespace qorai_ads {

PermissionRulesBase::PermissionRulesBase() = default;

PermissionRulesBase::~PermissionRulesBase() = default;

// static
bool PermissionRulesBase::HasPermission() {
  if (!HasIssuersPermission()) {
    return false;
  }

  if (!HasConfirmationTokensPermission()) {
    return false;
  }

  if (!HasCommandLinePermission()) {
    return false;
  }

  return true;
}

}  // namespace qorai_ads
