/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_policy/qorai_browser_policy_provider.h"

#include <utility>

#include "base/logging.h"
#include "base/values.h"
#include "qorai/components/qorai_origin/qorai_origin_utils.h"
#include "components/policy/core/common/policy_bundle.h"
#include "components/policy/core/common/policy_map.h"
#include "components/policy/core/common/policy_namespace.h"
#include "components/policy/core/common/policy_types.h"
#include "components/prefs/pref_service.h"

namespace qorai_policy {

QoraiBrowserPolicyProvider::QoraiBrowserPolicyProvider() = default;

QoraiBrowserPolicyProvider::~QoraiBrowserPolicyProvider() = default;

void QoraiBrowserPolicyProvider::Init(policy::SchemaRegistry* registry) {
  // Call base class Init first
  policy::ConfigurationPolicyProvider::Init(registry);

  // Register as QoraiOriginPolicyManager observer.
  // This ensures feature flags and local state are available before policy
  // loading.
  policy_manager_observation_.Observe(
      qorai_origin::QoraiOriginPolicyManager::GetInstance());
}

void QoraiBrowserPolicyProvider::RefreshPolicies(
    policy::PolicyFetchReason reason) {
  policy::PolicyBundle bundle = LoadPolicies();

  // Mark as loaded after successfully loading policies
  first_policies_loaded_ = true;

  UpdatePolicy(std::move(bundle));
}

bool QoraiBrowserPolicyProvider::IsFirstPolicyLoadComplete(
    policy::PolicyDomain domain) const {
  return first_policies_loaded_;
}

void QoraiBrowserPolicyProvider::OnQoraiPoliciesReady() {
  // Now that Qorai policies are ready, trigger policy loading for the
  // first time.
  RefreshPolicies(policy::PolicyFetchReason::kBrowserStart);
}

void QoraiBrowserPolicyProvider::OnBrowserPolicyChanged(
    std::string_view policy_key) {
  RefreshPolicies(policy::PolicyFetchReason::kUserRequest);
}

policy::PolicyBundle QoraiBrowserPolicyProvider::LoadPolicies() {
  policy::PolicyBundle bundle;

  // TODO(https://github.com/qorai/qorai-browser/issues/47463)
  // Get the actual purchase state from SKU service.
#if !defined(OFFICIAL_BUILD)
  if (qorai_origin::IsQoraiOriginEnabled()) {
    LoadQoraiOriginPolicies(bundle);
  }
#else
  // Always disabled in official builds
#endif

  return bundle;
}

std::unique_ptr<policy::ConfigurationPolicyProvider>
CreateQoraiBrowserPolicyProvider() {
  return std::make_unique<QoraiBrowserPolicyProvider>();
}

void QoraiBrowserPolicyProvider::LoadQoraiOriginPolicies(
    policy::PolicyBundle& bundle) {
  // Create policy map for Chrome domain
  policy::PolicyMap& bundle_policy_map = bundle.Get(
      policy::PolicyNamespace(policy::POLICY_DOMAIN_CHROME, std::string()));

  // Get all browser policies
  const auto policy_values =
      qorai_origin::QoraiOriginPolicyManager::GetInstance()
          ->GetAllBrowserPolicies();
  for (const auto& [policy_key, enabled] : policy_values) {
    LoadQoraiOriginPolicy(bundle_policy_map, policy_key, enabled);
  }
}

void QoraiBrowserPolicyProvider::LoadQoraiOriginPolicy(
    policy::PolicyMap& bundle_policy_map,
    std::string_view policy_key,
    bool enabled) {
  // Set the policy - the ConfigurationPolicyPrefStore will handle
  // converting this to the appropriate local state preference
  bundle_policy_map.Set(std::string(policy_key), policy::POLICY_LEVEL_MANDATORY,
                        policy::POLICY_SCOPE_USER, policy::POLICY_SOURCE_QORAI,
                        base::Value(enabled), nullptr);
}

}  // namespace qorai_policy
