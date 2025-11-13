// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_DARKER_THEME_FEATURES_H_
#define QORAI_BROWSER_UI_DARKER_THEME_FEATURES_H_

#include "base/feature_list.h"

namespace darker_theme::features {

// Feature to enable "Midnight Theme" which is darker than usual dark themes.
BASE_DECLARE_FEATURE(kQoraiDarkerTheme);

}  // namespace darker_theme::features

#endif  // QORAI_BROWSER_UI_DARKER_THEME_FEATURES_H_
