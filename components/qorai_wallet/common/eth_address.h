/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_COMMON_ETH_ADDRESS_H_
#define QORAI_COMPONENTS_QORAI_WALLET_COMMON_ETH_ADDRESS_H_

#include <string>
#include <vector>

#include "base/containers/span.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet_types.h"

namespace qorai_wallet {

inline constexpr size_t kEthAddressLength = 20u;

class EthAddress {
 public:
  // public key must be uncompressed and no header byte so its length is 64
  // bytes
  static EthAddress FromPublicKey(base::span<const uint8_t> public_key);
  // input should be a valid address with 20 bytes hex representation starting
  // with 0x
  static EthAddress FromHex(std::string_view input);
  static EthAddress FromBytes(base::span<const uint8_t> bytes);
  static EthAddress ZeroAddress();
  static bool IsValidAddress(std::string_view input);
  static std::optional<std::string> ToEip1191ChecksumAddress(
      std::string_view address,
      std::string_view chain_id);

  EthAddress();
  EthAddress(const EthAddress& other);
  ~EthAddress();
  bool operator==(const EthAddress& other) const;

  bool IsEmpty() const;
  bool IsValid() const;
  bool IsZeroAddress() const;
  const std::vector<uint8_t>& bytes() const { return bytes_; }

  std::string ToHex() const;
  // EIP55 + EIP1191
  std::string ToChecksumAddress(uint256_t eip1191_chaincode = 0) const;

 private:
  explicit EthAddress(std::vector<uint8_t> bytes);
  explicit EthAddress(base::span<const uint8_t> bytes);

  std::vector<uint8_t> bytes_;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_COMMON_ETH_ADDRESS_H_
