/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_POLICY_QORAI_POLICY_OBSERVER_H_
#define QORAI_COMPONENTS_QORAI_POLICY_QORAI_POLICY_OBSERVER_H_

#include <string_view>

#include "base/observer_list_types.h"

namespace qorai_policy {

// Observer interface for objects that need to be notified when
// Qorai policies are loaded/changed.
class QoraiPolicyObserver : public base::CheckedObserver {
 public:
  // Called when Qorai policies become available or are updated.
  virtual void OnQoraiPoliciesReady() = 0;

  // Called when a browser-level policy preference is changed.
  virtual void OnBrowserPolicyChanged(std::string_view policy_key) {}

  // Called when a profile-level policy preference is changed.
  virtual void OnProfilePolicyChanged(std::string_view policy_key,
                                      std::string_view profile_id) {}
};

}  // namespace qorai_policy

#endif  // QORAI_COMPONENTS_QORAI_POLICY_QORAI_POLICY_OBSERVER_H_
