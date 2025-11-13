/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_BITCOIN_BITCOIN_IMPORT_KEYRING_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_BITCOIN_BITCOIN_IMPORT_KEYRING_H_

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "qorai/components/qorai_wallet/browser/bitcoin/bitcoin_base_keyring.h"
#include "qorai/components/qorai_wallet/browser/internal/hd_key.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

namespace qorai_wallet {

class BitcoinImportKeyring : public BitcoinBaseKeyring {
 public:
  explicit BitcoinImportKeyring(mojom::KeyringId keyring_id);
  ~BitcoinImportKeyring() override;
  BitcoinImportKeyring(const BitcoinImportKeyring&) = delete;
  BitcoinImportKeyring& operator=(const BitcoinImportKeyring&) = delete;

  bool AddAccount(uint32_t account, const std::string& payload);
  bool RemoveAccount(uint32_t account);

  // BitcoinBaseKeyring:
  mojom::BitcoinAddressPtr GetAddress(
      uint32_t account,
      const mojom::BitcoinKeyId& key_id) override;
  std::optional<std::vector<uint8_t>> GetPubkey(
      uint32_t account,
      const mojom::BitcoinKeyId& key_id) override;
  std::optional<std::vector<uint8_t>> SignMessage(
      uint32_t account,
      const mojom::BitcoinKeyId& key_id,
      base::span<const uint8_t, 32> message) override;

 private:
  std::map<uint32_t, std::unique_ptr<HDKey>> accounts_;
  HDKey* GetAccountByIndex(uint32_t account);

  std::unique_ptr<HDKey> DeriveKey(uint32_t account,
                                   const mojom::BitcoinKeyId& key_id);
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_BITCOIN_BITCOIN_IMPORT_KEYRING_H_
