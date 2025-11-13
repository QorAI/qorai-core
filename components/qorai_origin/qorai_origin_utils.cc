/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_origin/qorai_origin_utils.h"

#include "base/feature_list.h"
#include "base/logging.h"
#include "base/strings/strcat.h"
#include "qorai/components/qorai_origin/qorai_origin_policy_info.h"
#include "qorai/components/qorai_origin/features.h"

namespace qorai_origin {

bool IsQoraiOriginEnabled() {
  // TODO(https://github.com/qorai/qorai-browser/issues/47463)
  // Get the actual purchase state from SKU service.
  return base::FeatureList::IsEnabled(features::kQoraiOrigin);
}

std::string GetQoraiOriginPrefKey(std::string_view policy_key,
                                  std::optional<std::string_view> profile_id) {
  if (!profile_id.has_value()) {
    return std::string(policy_key);
  }

  // For profile prefs, use profile_id.policy_key format
  CHECK(!profile_id.value().empty());
  return base::StrCat({profile_id.value(), ".", policy_key});
}

}  // namespace qorai_origin
