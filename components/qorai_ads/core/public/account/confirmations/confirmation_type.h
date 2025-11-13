/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_ACCOUNT_CONFIRMATIONS_CONFIRMATION_TYPE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_ACCOUNT_CONFIRMATIONS_CONFIRMATION_TYPE_H_

#include <string_view>

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

// Returns a `mojom::ConfirmationType` value based on the string input.
mojom::ConfirmationType ToMojomConfirmationType(std::string_view value);

// Returns a string constant for a given `mojom::ConfirmationType` value.
std::string_view ToString(mojom::ConfirmationType value);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_PUBLIC_ACCOUNT_CONFIRMATIONS_CONFIRMATION_TYPE_H_
