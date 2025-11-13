/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_NON_CASH_DEPOSIT_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_NON_CASH_DEPOSIT_H_

#include <string>

#include "qorai/components/qorai_ads/core/internal/account/deposits/deposit_interface.h"

namespace qorai_ads {

class NonCashDeposit final : public DepositInterface {
 public:
  void GetValue(const std::string& creative_instance_id,
                GetDepositCallback callback) override;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_NON_CASH_DEPOSIT_H_
