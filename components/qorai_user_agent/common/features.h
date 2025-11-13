// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_USER_AGENT_COMMON_FEATURES_H_
#define QORAI_COMPONENTS_QORAI_USER_AGENT_COMMON_FEATURES_H_

#include "base/component_export.h"
#include "base/feature_list.h"

namespace qorai_user_agent {
namespace features {

COMPONENT_EXPORT(QORAI_USER_AGENT_COMMON)
BASE_DECLARE_FEATURE(kUseQoraiUserAgent);

}  // namespace features
}  // namespace qorai_user_agent

#endif  // QORAI_COMPONENTS_QORAI_USER_AGENT_COMMON_FEATURES_H_
