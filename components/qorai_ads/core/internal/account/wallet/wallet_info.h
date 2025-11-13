/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_WALLET_WALLET_INFO_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_WALLET_WALLET_INFO_H_

#include <string>

namespace qorai_ads {

struct WalletInfo final {
  bool operator==(const WalletInfo&) const = default;

  [[nodiscard]] bool IsValid() const;

  std::string payment_id;
  std::string public_key_base64;
  std::string secret_key_base64;
};

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_WALLET_WALLET_INFO_H_
