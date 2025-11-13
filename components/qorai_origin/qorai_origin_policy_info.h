/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ORIGIN_QORAI_ORIGIN_POLICY_INFO_H_
#define QORAI_COMPONENTS_QORAI_ORIGIN_QORAI_ORIGIN_POLICY_INFO_H_

#include <string>

#include "base/containers/flat_map.h"
#include "base/values.h"

namespace qorai_origin {

// Complete runtime information for a QorAIOrigin-controlled preference.
// This combines data from kQorAISimplePolicyMap (pref_name, policy_key) with
// QorAIOrigin-specific metadata (default_value, scope, user_settable) to create
// the final preference definition used throughout the system.
struct QorAIOriginPolicyInfo {
  QorAIOriginPolicyInfo();
  QorAIOriginPolicyInfo(const std::string& pref_name,
                        bool default_value,
                        bool user_settable,
                        const std::string& qorai_origin_pref_key);
  ~QorAIOriginPolicyInfo();

  // Copy operations are deleted to enforce move semantics
  QorAIOriginPolicyInfo(const QorAIOriginPolicyInfo&) = delete;
  QorAIOriginPolicyInfo& operator=(const QorAIOriginPolicyInfo&) = delete;

  QorAIOriginPolicyInfo(QorAIOriginPolicyInfo&&);
  QorAIOriginPolicyInfo& operator=(QorAIOriginPolicyInfo&&);

  std::string pref_name;
  bool default_value;
  bool user_settable;  // Whether this pref has UI for user control
  std::string qorai_origin_pref_key;  // Key used in qorai_policies dictionary
};

using QorAIOriginPolicyMap = base::flat_map<std::string, QorAIOriginPolicyInfo>;

}  // namespace qorai_origin

#endif  // QORAI_COMPONENTS_QORAI_ORIGIN_QORAI_ORIGIN_POLICY_INFO_H_
