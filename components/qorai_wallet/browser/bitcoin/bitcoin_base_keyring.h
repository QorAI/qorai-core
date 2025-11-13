/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_BITCOIN_BITCOIN_BASE_KEYRING_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_BITCOIN_BITCOIN_BASE_KEYRING_H_

#include <optional>
#include <vector>

#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

namespace qorai_wallet {

class BitcoinBaseKeyring {
 public:
  explicit BitcoinBaseKeyring(mojom::KeyringId keyring_id);
  virtual ~BitcoinBaseKeyring();

  virtual mojom::BitcoinAddressPtr GetAddress(
      uint32_t account,
      const mojom::BitcoinKeyId& key_id) = 0;

  virtual std::optional<std::vector<uint8_t>> GetPubkey(
      uint32_t account,
      const mojom::BitcoinKeyId& key_id) = 0;

  virtual std::optional<std::vector<uint8_t>> SignMessage(
      uint32_t account,
      const mojom::BitcoinKeyId& key_id,
      base::span<const uint8_t, 32> message) = 0;

  mojom::KeyringId keyring_id() const { return keyring_id_; }
  bool IsTestnet() const;

 protected:
  mojom::KeyringId keyring_id_;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_BITCOIN_BITCOIN_BASE_KEYRING_H_
