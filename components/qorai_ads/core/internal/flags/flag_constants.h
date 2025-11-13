/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_FLAGS_FLAG_CONSTANTS_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_FLAGS_FLAG_CONSTANTS_H_

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"
#include "build/build_config.h"

namespace qorai_ads {

#if defined(OFFICIAL_BUILD)
inline constexpr mojom::EnvironmentType kDefaultEnvironmentType =
    mojom::EnvironmentType::kProduction;
#else   // OFFICIAL_BUILD
inline constexpr mojom::EnvironmentType kDefaultEnvironmentType =
    mojom::EnvironmentType::kStaging;
#endif  // !OFFICIAL_BUILD

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_FLAGS_FLAG_CONSTANTS_H_
