// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_QORAI_UI_FEATURES_H_
#define QORAI_BROWSER_UI_QORAI_UI_FEATURES_H_

#include "base/feature_list.h"
#include "build/build_config.h"

namespace features {

BASE_DECLARE_FEATURE(kQoraiNtpSearchWidget);
#if BUILDFLAG(IS_WIN)
BASE_DECLARE_FEATURE(kQoraiWorkaroundNewWindowFlash);
#endif  // BUILDFLAG(IS_WIN)

}  // namespace features

#endif  // QORAI_BROWSER_UI_QORAI_UI_FEATURES_H_
