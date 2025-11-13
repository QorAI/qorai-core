/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_FILECOIN_KEYRING_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_FILECOIN_KEYRING_H_

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "qorai/components/qorai_wallet/browser/fil_transaction.h"
#include "qorai/components/qorai_wallet/browser/secp256k1_hd_keyring.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet_types.h"

namespace qorai_wallet {

class FilTransaction;

class FilecoinKeyring : public Secp256k1HDKeyring {
 public:
  FilecoinKeyring(base::span<const uint8_t> seed, mojom::KeyringId keyring_id);
  ~FilecoinKeyring() override;
  FilecoinKeyring(const FilecoinKeyring&) = delete;
  FilecoinKeyring& operator=(const FilecoinKeyring&) = delete;
  static bool DecodeImportPayload(const std::string& payload_hex,
                                  std::vector<uint8_t>* private_key_out,
                                  mojom::FilecoinAddressProtocol* protocol_out);
  std::optional<std::string> ImportFilecoinAccount(
      base::span<const uint8_t> private_key,
      mojom::FilecoinAddressProtocol protocol);
  bool RemoveImportedAccount(const std::string& address);

  std::optional<std::string> SignTransaction(const std::string& address,
                                             const FilTransaction& tx);

  std::optional<std::string> GetDiscoveryAddress(size_t index) const;
  std::optional<std::string> EncodePrivateKeyForExport(
      const std::string& address);
  std::vector<std::string> GetImportedAccountsForTesting() const;

  mojom::KeyringId keyring_id() const { return keyring_id_; }

 private:
  std::optional<std::string> ImportBlsAccount(
      base::span<const uint8_t> private_key);
  std::string GetAddressInternal(const HDKey& hd_key) const override;
  std::unique_ptr<HDKey> DeriveAccount(uint32_t index) const override;
  mojom::KeyringId keyring_id_;
  std::string network_;

  // TODO(apaymyshev): BLS keys are neither Secp256k1 keys nor HD keys. Should
  // not belong there.
  base::flat_map<std::string, std::unique_ptr<SecureVector>>
      imported_bls_accounts_;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_FILECOIN_KEYRING_H_
