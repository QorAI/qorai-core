/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTIONS_TEST_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTIONS_TEST_UTIL_H_

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace base {
class Time;
}  // namespace base

namespace qorai_ads {

struct TransactionInfo;

namespace test {

TransactionInfo BuildTransaction(
    double value,
    mojom::AdType mojom_ad_type,
    mojom::ConfirmationType mojom_confirmation_type,
    base::Time reconciled_at,
    bool should_generate_random_uuids);
TransactionInfo BuildUnreconciledTransaction(
    double value,
    mojom::AdType mojom_ad_type,
    mojom::ConfirmationType mojom_confirmation_type,
    bool should_generate_random_uuids);

}  // namespace test

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_TRANSACTIONS_TRANSACTIONS_TEST_UTIL_H_
