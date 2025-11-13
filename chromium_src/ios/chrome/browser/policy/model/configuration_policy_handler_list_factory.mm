/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "ios/chrome/browser/policy/model/configuration_policy_handler_list_factory.h"

#include <memory>

#define BuildPolicyHandlerList BuildPolicyHandlerList_ChromiumImpl
#include <ios/chrome/browser/policy/model/configuration_policy_handler_list_factory.mm>
#undef BuildPolicyHandlerList

namespace qorai {
std::unique_ptr<policy::ConfigurationPolicyHandlerList> BuildPolicyHandlerList(
    std::unique_ptr<policy::ConfigurationPolicyHandlerList> handlers);
}

std::unique_ptr<policy::ConfigurationPolicyHandlerList> BuildPolicyHandlerList(
    bool are_future_policies_allowed_by_default,
    const policy::Schema& chrome_schema) {
  std::unique_ptr<policy::ConfigurationPolicyHandlerList> handlers =
      BuildPolicyHandlerList_ChromiumImpl(
          are_future_policies_allowed_by_default, chrome_schema);
  return qorai::BuildPolicyHandlerList(std::move(handlers));
}
