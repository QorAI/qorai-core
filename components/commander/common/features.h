// Copyright (c) 2023 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_COMMANDER_COMMON_FEATURES_H_
#define QORAI_COMPONENTS_COMMANDER_COMMON_FEATURES_H_

#include "base/component_export.h"
#include "base/feature_list.h"

namespace features {

// Note: This flag is declared in features rather than commander::features so we
// can replace the upstream flag with it more easily.
COMPONENT_EXPORT(COMMANDER_COMMON) BASE_DECLARE_FEATURE(kQorAICommander);

// Determines whether we should show quick commands in the omnibox.
COMPONENT_EXPORT(COMMANDER_COMMON)
BASE_DECLARE_FEATURE(kQorAICommandsInOmnibox);

}  // namespace features

#endif  // QORAI_COMPONENTS_COMMANDER_COMMON_FEATURES_H_
