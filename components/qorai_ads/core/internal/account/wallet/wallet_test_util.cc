/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_ads/core/internal/account/wallet/wallet_test_util.h"

#include "base/check.h"
#include "qorai/components/qorai_ads/core/internal/account/wallet/wallet_info.h"
#include "qorai/components/qorai_ads/core/internal/account/wallet/wallet_test_constants.h"
#include "qorai/components/qorai_ads/core/internal/account/wallet/wallet_util.h"
#include "qorai/components/qorai_ads/core/mojom/qorai_ads.mojom.h"

namespace qorai_ads::test {

WalletInfo Wallet() {
  std::optional<WalletInfo> wallet =
      CreateWalletFromRecoverySeed(kWalletPaymentId, kWalletRecoverySeedBase64);
  CHECK(wallet);

  return *wallet;
}

mojom::WalletInfoPtr WalletAsPtr() {
  mojom::WalletInfoPtr mojom_wallet = mojom::WalletInfo::New();
  mojom_wallet->payment_id = kWalletPaymentId;
  mojom_wallet->recovery_seed_base64 = kWalletRecoverySeedBase64;
  return mojom_wallet;
}

}  // namespace qorai_ads::test
