/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATION_TYPE_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATION_TYPE_TEST_UTIL_H_

#include <cstddef>
#include <vector>

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads::test {

std::vector<mojom::ConfirmationType>
BuildConfirmationTypeForCountAndIntersperseOtherTypes(
    mojom::ConfirmationType mojom_confirmation_type,
    size_t count);

}  // namespace qorai_ads::test

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_CONFIRMATIONS_CONFIRMATION_TYPE_TEST_UTIL_H_
