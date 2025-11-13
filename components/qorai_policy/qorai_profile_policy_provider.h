/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_POLICY_QORAI_PROFILE_POLICY_PROVIDER_H_
#define QORAI_COMPONENTS_QORAI_POLICY_QORAI_PROFILE_POLICY_PROVIDER_H_

#include "base/containers/flat_set.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "base/values.h"
#include "qorai/components/qorai_origin/qorai_origin_policy_info.h"
#include "qorai/components/qorai_origin/qorai_origin_policy_manager.h"
#include "qorai/components/qorai_policy/ad_block_only_mode/ad_block_only_mode_policy_manager.h"
#include "qorai/components/qorai_policy/qorai_policy_observer.h"
#include "components/policy/core/common/configuration_policy_provider.h"

namespace qorai_policy {

// Policy provider for profile level policies.
// Note: When this is created, the profile is not yet initialized.
class QoraiProfilePolicyProvider : public policy::ConfigurationPolicyProvider,
                                   public QoraiPolicyObserver {
 public:
  QoraiProfilePolicyProvider();
  ~QoraiProfilePolicyProvider() override;

  QoraiProfilePolicyProvider(const QoraiProfilePolicyProvider&) = delete;
  QoraiProfilePolicyProvider& operator=(const QoraiProfilePolicyProvider&) =
      delete;

  // ConfigurationPolicyProvider implementation.
  void Init(policy::SchemaRegistry* registry) override;
  void RefreshPolicies(policy::PolicyFetchReason reason) override;
  bool IsFirstPolicyLoadComplete(policy::PolicyDomain domain) const override;

  // QoraiPolicyObserver implementation.
  void OnQoraiPoliciesReady() override;
  void OnProfilePolicyChanged(std::string_view policy_key,
                              std::string_view profile_id) override;
  void SetProfileID(const std::string& profile_id);

 private:
  policy::PolicyBundle LoadPolicies();

  // Helper to load QoraiOrigin profile policies
  void LoadQoraiOriginPolicies(policy::PolicyBundle& bundle);
  void LoadQoraiOriginPolicy(policy::PolicyMap& bundle_policy_map,
                             std::string_view policy_key,
                             bool enabled);

  void MaybeLoadAdBlockOnlyModePolicies(policy::PolicyBundle& bundle);

  bool first_policies_loaded_ = false;
  bool policies_ready_ = false;
  std::string profile_id_;

  base::ScopedObservation<qorai_origin::QoraiOriginPolicyManager,
                          QoraiPolicyObserver>
      qorai_origin_observation_{this};

  base::ScopedObservation<AdBlockOnlyModePolicyManager, QoraiPolicyObserver>
      ad_block_only_mode_policy_observation_{this};

  base::WeakPtrFactory<QoraiProfilePolicyProvider> weak_factory_{this};
};

}  // namespace qorai_policy

#endif  // QORAI_COMPONENTS_QORAI_POLICY_QORAI_PROFILE_POLICY_PROVIDER_H_
