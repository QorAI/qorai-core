/* Copyright (c) 2024 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_WEB_DISCOVERY_COMMON_FEATURES_H_
#define QORAI_COMPONENTS_WEB_DISCOVERY_COMMON_FEATURES_H_

#include <string>

#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"

namespace web_discovery::features {

// Enables the native re-implementation of the Web Discovery Project.
// If enabled, the Web Discovery component of the extension should be disabled.
BASE_DECLARE_FEATURE(kQorAIWebDiscoveryNative);
extern const base::FeatureParam<std::string> kPatternsPath;

}  // namespace web_discovery::features

#endif  // QORAI_COMPONENTS_WEB_DISCOVERY_COMMON_FEATURES_H_
