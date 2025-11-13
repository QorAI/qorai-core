/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_SERVICES_QORAI_WALLET_ZCASH_ZCASH_DECODER_H_
#define QORAI_COMPONENTS_SERVICES_QORAI_WALLET_ZCASH_ZCASH_DECODER_H_

#include "qorai/components/services/qorai_wallet/public/mojom/zcash_decoder.mojom.h"

#include <string>
#include <vector>

#include "mojo/public/cpp/bindings/receiver_set.h"

namespace qorai_wallet {

// Parses Zcash protobuf objects and translates them to mojo.
class ZCashDecoder : public zcash::mojom::ZCashDecoder {
 public:
  ZCashDecoder();
  ~ZCashDecoder() override;

  ZCashDecoder(const ZCashDecoder&) = delete;
  ZCashDecoder& operator=(const ZCashDecoder&) = delete;

  void ParseRawTransaction(const std::string& data,
                           ParseRawTransactionCallback callback) override;
  void ParseBlockID(const std::string& data,
                    ParseBlockIDCallback callback) override;
  void ParseGetAddressUtxos(const std::string& data,
                            ParseGetAddressUtxosCallback callback) override;
  void ParseSendResponse(const std::string& data,
                         ParseSendResponseCallback) override;
  void ParseTreeState(const std::string& data,
                      ParseTreeStateCallback callback) override;
  void ParseCompactBlocks(const std::vector<std::string>& data,
                          ParseCompactBlocksCallback callback) override;
  void ParseLightdInfo(const std::string& data,
                       ParseLightdInfoCallback callback) override;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_SERVICES_QORAI_WALLET_ZCASH_ZCASH_DECODER_H_
