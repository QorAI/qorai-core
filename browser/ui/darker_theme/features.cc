// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/darker_theme/features.h"

namespace darker_theme::features {

// Note that we're exposing the feature with the name "QoraiMidnightTheme" for
// brand consistency
BASE_FEATURE(kQoraiDarkerTheme,
             "QoraiMidnightTheme",
             base::FEATURE_DISABLED_BY_DEFAULT);

}  // namespace darker_theme::features
