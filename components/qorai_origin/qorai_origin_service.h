/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ORIGIN_QORAI_ORIGIN_SERVICE_H_
#define QORAI_COMPONENTS_QORAI_ORIGIN_QORAI_ORIGIN_SERVICE_H_

#include <optional>

#include "base/memory/raw_ptr.h"
#include "base/values.h"
#include "qorai/components/qorai_origin/qorai_origin_policy_info.h"
#include "components/keyed_service/core/keyed_service.h"

class PrefService;

namespace policy {
class PolicyService;
}  // namespace policy

namespace qorai_origin {

// This keyed service will maintain the definitions/mappings of policies to
// preferences.
//
// This is separate from QoraiProfilePolicyProvider which handles the actual
// integration with Chromium's policy framework.
class QoraiOriginService : public KeyedService {
 public:
  explicit QoraiOriginService(PrefService* local_state,
                              PrefService* profile_prefs,
                              std::string_view profile_id,
                              policy::PolicyService* profile_policy_service,
                              policy::PolicyService* browser_policy_service);
  ~QoraiOriginService() override;

  // Check if a policy is controlled by QoraiOrigin
  bool IsPolicyControlledByQoraiOrigin(std::string_view policy_key) const;

  // Update the QoraiOrigin policy value
  bool SetPolicyValue(std::string_view policy_key, bool value);

  // Get the current value of a QoraiOrigin policy
  std::optional<bool> GetPolicyValue(std::string_view policy_key) const;

 protected:
  // Local state and profile preferences this state is associated with
  raw_ptr<PrefService> local_state_;
  raw_ptr<PrefService> profile_prefs_;

  // The profile_id is a calculated hash which will be used to look up
  // the policy values for a particular profile.
  std::string profile_id_;
  raw_ptr<policy::PolicyService> profile_policy_service_;
  raw_ptr<policy::PolicyService> browser_policy_service_;
};

}  // namespace qorai_origin

#endif  // QORAI_COMPONENTS_QORAI_ORIGIN_QORAI_ORIGIN_SERVICE_H_
