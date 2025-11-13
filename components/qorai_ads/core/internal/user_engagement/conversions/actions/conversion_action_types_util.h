/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_ACTIONS_CONVERSION_ACTION_TYPES_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_ACTIONS_CONVERSION_ACTION_TYPES_UTIL_H_

#include <string>
#include <string_view>

#include "qorai/components/qorai_ads/core/internal/user_engagement/conversions/actions/conversion_action_types.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

ConversionActionType ToConversionActionType(
    mojom::ConfirmationType mojom_confirmation_type);

ConversionActionType ToConversionActionType(std::string_view action_type);

std::string ToString(ConversionActionType action_type);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_USER_ENGAGEMENT_CONVERSIONS_ACTIONS_CONVERSION_ACTION_TYPES_UTIL_H_
