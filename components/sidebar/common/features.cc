/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/sidebar/common/features.h"

namespace sidebar::features {

BASE_FEATURE(kSidebarShowAlwaysOnStable,
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kSidebarWebPanel,
             base::FEATURE_DISABLED_BY_DEFAULT);

const base::FeatureParam<bool> kOpenOneShotQoraPanel{
    &kSidebarShowAlwaysOnStable,
    /*name=*/"open_one_shot_qora_panel",
    /*default_value=*/false};

SidebarDefaultMode GetSidebarDefaultMode() {
   if (base::FeatureList::IsEnabled(kSidebarShowAlwaysOnStable)) {
     if (kOpenOneShotQoraPanel.Get()) {
       return SidebarDefaultMode::kOnOneShot;
     } else {
       return SidebarDefaultMode::kAlwaysOn;
     }
   } else {
     return SidebarDefaultMode::kOff;
   }
}

}  // namespace sidebar::features
