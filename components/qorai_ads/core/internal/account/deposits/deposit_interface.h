/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSIT_INTERFACE_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSIT_INTERFACE_H_

#include <string>

#include "base/functional/callback.h"

namespace qorai_ads {

using GetDepositCallback = base::OnceCallback<void(bool success, double value)>;

class DepositInterface {
 public:
  virtual ~DepositInterface() = default;

  // Returns the deposit value for the given `creative_instance_id`.
  virtual void GetValue(const std::string& creative_instance_id,
                        GetDepositCallback callback) = 0;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_DEPOSITS_DEPOSIT_INTERFACE_H_
