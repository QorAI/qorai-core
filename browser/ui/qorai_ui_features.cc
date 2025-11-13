// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/qorai_ui_features.h"

namespace features {

BASE_FEATURE(kQoraiNtpSearchWidget,
             base::FEATURE_ENABLED_BY_DEFAULT);

#if BUILDFLAG(IS_WIN)
// Enables window cloaking on window creation to prevent a white flash.
BASE_FEATURE(kQoraiWorkaroundNewWindowFlash,
             base::FEATURE_ENABLED_BY_DEFAULT);
#endif  // BUILDFLAG(IS_WIN)

}  // namespace features
