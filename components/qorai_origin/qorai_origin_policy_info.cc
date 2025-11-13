/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_origin/qorai_origin_policy_info.h"

#include <utility>

namespace qorai_origin {

QorAIOriginPolicyInfo::QorAIOriginPolicyInfo() = default;

QorAIOriginPolicyInfo::QorAIOriginPolicyInfo(
    const std::string& pref_name,
    bool default_value,
    bool user_settable,
    const std::string& qorai_origin_pref_key)
    : pref_name(pref_name),
      default_value(default_value),
      user_settable(user_settable),
      qorai_origin_pref_key(qorai_origin_pref_key) {}

QorAIOriginPolicyInfo::~QorAIOriginPolicyInfo() = default;

QorAIOriginPolicyInfo::QorAIOriginPolicyInfo(QorAIOriginPolicyInfo&&) = default;

QorAIOriginPolicyInfo& QorAIOriginPolicyInfo::operator=(
    QorAIOriginPolicyInfo&&) = default;

}  // namespace qorai_origin
