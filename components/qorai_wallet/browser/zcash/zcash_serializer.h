/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_SERIALIZER_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_SERIALIZER_H_

#include <array>
#include <string>
#include <vector>

#include "base/gtest_prod_util.h"
#include "qorai/components/qorai_wallet/browser/keyring_service.h"
#include "qorai/components/qorai_wallet/browser/zcash/zcash_keyring.h"
#include "qorai/components/qorai_wallet/browser/zcash/zcash_transaction.h"

namespace qorai_wallet {

// Implements algorithms for calculaction tx id, tx signature digest
// https://zips.z.cash/zip-0244
class ZCashSerializer {
 public:
  static std::array<uint8_t, kZCashDigestSize> CalculateTxIdDigest(
      const ZCashTransaction& zcash_transaction);
  static std::array<uint8_t, kZCashDigestSize> CalculateSignatureDigest(
      const ZCashTransaction& zcash_transaction,
      const std::optional<ZCashTransaction::TxInput>& input);
  static std::vector<uint8_t> SerializeRawTransaction(
      const ZCashTransaction& zcash_transaction);
  static bool SignTransparentPart(KeyringService& keyring_service,
                                  const mojom::AccountIdPtr& account_id,
                                  ZCashTransaction& tx);

 private:
  FRIEND_TEST_ALL_PREFIXES(ZCashSerializerTest, HashHeader);
  FRIEND_TEST_ALL_PREFIXES(ZCashSerializerTest, HashOutputs);
  FRIEND_TEST_ALL_PREFIXES(ZCashSerializerTest, HashPrevouts);
  FRIEND_TEST_ALL_PREFIXES(ZCashSerializerTest, HashSequences);
  FRIEND_TEST_ALL_PREFIXES(ZCashSerializerTest, HashTxIn);
  FRIEND_TEST_ALL_PREFIXES(ZCashSerializerTest, OrchardBundle);

  static void SerializeSignature(const ZCashTransaction& tx,
                                 ZCashTransaction::TxInput& input,
                                 const std::vector<uint8_t>& pubkey,
                                 const std::vector<uint8_t>& signature);

  static std::array<uint8_t, kZCashDigestSize> HashHeader(
      const ZCashTransaction& tx);
  static std::array<uint8_t, kZCashDigestSize> HashPrevouts(
      const ZCashTransaction& tx);
  static std::array<uint8_t, kZCashDigestSize> HashSequences(
      const ZCashTransaction& tx);
  static std::array<uint8_t, kZCashDigestSize> HashOutputs(
      const ZCashTransaction& tx);
  static std::array<uint8_t, kZCashDigestSize> HashTxIn(
      std::optional<ZCashTransaction::TxInput> tx_in);
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_SERIALIZER_H_
