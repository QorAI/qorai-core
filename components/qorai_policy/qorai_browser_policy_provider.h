/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_POLICY_QORAI_BROWSER_POLICY_PROVIDER_H_
#define QORAI_COMPONENTS_QORAI_POLICY_QORAI_BROWSER_POLICY_PROVIDER_H_

#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "qorai/components/qorai_origin/qorai_origin_policy_info.h"
#include "qorai/components/qorai_origin/qorai_origin_policy_manager.h"
#include "qorai/components/qorai_policy/qorai_policy_observer.h"
#include "components/policy/core/common/configuration_policy_provider.h"

namespace qorai_policy {

// Browser-level policy provider for global scope preferences.
// This provider handles policies that affect global preferences
// and is registered with the BrowserPolicyConnector for machine-wide policy
// management.
class QoraiBrowserPolicyProvider : public policy::ConfigurationPolicyProvider,
                                   public QoraiPolicyObserver {
 public:
  QoraiBrowserPolicyProvider();
  ~QoraiBrowserPolicyProvider() override;

  QoraiBrowserPolicyProvider(const QoraiBrowserPolicyProvider&) = delete;
  QoraiBrowserPolicyProvider& operator=(const QoraiBrowserPolicyProvider&) =
      delete;

  // ConfigurationPolicyProvider implementation.
  void Init(policy::SchemaRegistry* registry) override;
  void RefreshPolicies(policy::PolicyFetchReason reason) override;
  bool IsFirstPolicyLoadComplete(policy::PolicyDomain domain) const override;

  // QoraiPolicyObserver implementation.
  void OnQoraiPoliciesReady() override;
  void OnBrowserPolicyChanged(std::string_view policy_key) override;

 private:
  // Loads policies for browser scope preferences only.
  policy::PolicyBundle LoadPolicies();

  // Helper to set QoraiOrigin policy for a specific preference
  void LoadQoraiOriginPolicies(policy::PolicyBundle& bundle);
  void LoadQoraiOriginPolicy(policy::PolicyMap& policy_map,
                             std::string_view policy_key,
                             bool enabled);

  bool first_policies_loaded_ = false;

  base::ScopedObservation<qorai_origin::QoraiOriginPolicyManager,
                          QoraiPolicyObserver>
      policy_manager_observation_{this};

  base::WeakPtrFactory<QoraiBrowserPolicyProvider> weak_factory_{this};
};

}  // namespace qorai_policy

#endif  // QORAI_COMPONENTS_QORAI_POLICY_QORAI_BROWSER_POLICY_PROVIDER_H_
