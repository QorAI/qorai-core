/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/browser/policy/chrome_browser_policy_connector.h"

// Forward declare functions that will be implemented in
// qorai_browser_policy_provider.cc This is done so that we don't need to depend
// on anything in the qorai layer here. Otherwise we'd have a circular
// dependency.
namespace qorai_policy {
std::unique_ptr<policy::ConfigurationPolicyProvider>
CreateQoraiBrowserPolicyProvider();
}  // namespace qorai_policy

// Rename CreatePolicyProviders to CreatePolicyProviders_ChromiumImpl
#define CreatePolicyProviders CreatePolicyProviders_ChromiumImpl

#include <chrome/browser/policy/chrome_browser_policy_connector.cc>  // IWYU pragma: export

#undef CreatePolicyProviders

// And define the new one
namespace policy {

std::vector<std::unique_ptr<policy::ConfigurationPolicyProvider>>
ChromeBrowserPolicyConnector::CreatePolicyProviders() {
  auto providers =
      ChromeBrowserPolicyConnector::CreatePolicyProviders_ChromiumImpl();
  // Add browser policy provider for browser-level (local state) policies
  auto qorai_browser_provider =
      ::qorai_policy::CreateQoraiBrowserPolicyProvider();
  // providers takes ownership of qorai_browser_provider
  providers.push_back(std::move(qorai_browser_provider));
  return providers;
}

}  // namespace policy
