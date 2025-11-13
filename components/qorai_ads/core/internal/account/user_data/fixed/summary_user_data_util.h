/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_SUMMARY_USER_DATA_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_SUMMARY_USER_DATA_UTIL_H_

#include "base/containers/flat_map.h"
#include "qorai/components/qorai_ads/core/internal/account/tokens/payment_tokens/payment_token_info.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

using ConfirmationTypeBucketMap =
    base::flat_map<mojom::ConfirmationType, /*count*/ int>;
using AdTypeBucketMap =
    base::flat_map<mojom::AdType, ConfirmationTypeBucketMap>;

AdTypeBucketMap BuildAdTypeBuckets(const PaymentTokenList& payment_tokens);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_USER_DATA_FIXED_SUMMARY_USER_DATA_UTIL_H_
