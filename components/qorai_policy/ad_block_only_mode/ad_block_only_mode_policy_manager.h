/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_POLICY_AD_BLOCK_ONLY_MODE_AD_BLOCK_ONLY_MODE_POLICY_MANAGER_H_
#define QORAI_COMPONENTS_QORAI_POLICY_AD_BLOCK_ONLY_MODE_AD_BLOCK_ONLY_MODE_POLICY_MANAGER_H_

#include "base/containers/flat_map.h"
#include "base/memory/raw_ptr.h"
#include "base/observer_list.h"
#include "base/values.h"
#include "qorai/components/qorai_policy/qorai_policy_observer.h"
#include "components/prefs/pref_change_registrar.h"

namespace base {
template <typename T>
class NoDestructor;
}

class PrefService;

namespace qorai_policy {

using AdBlockOnlyModePolicies = base::flat_map<std::string, base::Value>;

// Singleton that holds Ad Block Only mode preference handling and manages
// setting policy values when the preference is changed. This
// abstracts away the local state management from policy provider.
// TODO(https://github.com/qorai/qorai-browser/issues/50077): Refactor this
// class when `QoraiPolicyManager` is introduced.
class AdBlockOnlyModePolicyManager final {
 public:
  static AdBlockOnlyModePolicyManager* GetInstance();

  void Init(PrefService* local_state);
  void Shutdown();

  void AddObserver(QoraiPolicyObserver* observer);
  void RemoveObserver(QoraiPolicyObserver* observer);

  AdBlockOnlyModePolicies GetPolicies() const;

  AdBlockOnlyModePolicyManager(const AdBlockOnlyModePolicyManager&) = delete;
  AdBlockOnlyModePolicyManager& operator=(const AdBlockOnlyModePolicyManager&) =
      delete;

 private:
  friend base::NoDestructor<AdBlockOnlyModePolicyManager>;
  AdBlockOnlyModePolicyManager();
  ~AdBlockOnlyModePolicyManager();

  void OnAdBlockOnlyModeChanged();
  AdBlockOnlyModePolicies GetPoliciesImpl() const;

  raw_ptr<PrefService> local_state_;  // Not owned.
  PrefChangeRegistrar pref_change_registrar_;
  base::ObserverList<QoraiPolicyObserver> observers_;
};

}  // namespace qorai_policy

#endif  // QORAI_COMPONENTS_QORAI_POLICY_AD_BLOCK_ONLY_MODE_AD_BLOCK_ONLY_MODE_POLICY_MANAGER_H_
