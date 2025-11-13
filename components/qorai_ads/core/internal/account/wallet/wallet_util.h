/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_WALLET_WALLET_UTIL_H_
#define QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_WALLET_WALLET_UTIL_H_

#include <optional>
#include <string>

#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom-forward.h"

namespace qorai_ads {

struct WalletInfo;

std::optional<WalletInfo> CreateWalletFromRecoverySeed(
    const std::string& payment_id,
    const std::string& recovery_seed_base64);

std::optional<WalletInfo> CreateWalletFromRecoverySeed(
    const mojom::WalletInfo* mojom_wallet);

}  // namespace qorai_ads

#endif  // QORAI_COMPONENTS_QORAI_ADS_CORE_INTERNAL_ACCOUNT_WALLET_WALLET_UTIL_H_
