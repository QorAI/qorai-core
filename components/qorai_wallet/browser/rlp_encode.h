/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_RLP_ENCODE_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_RLP_ENCODE_H_

#include <vector>

#include "base/values.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet_types.h"

namespace qorai_wallet {

// Converts a uint256_t value into a blob value type
base::Value::BlobStorage RLPUint256ToBlob(uint256_t input);

// Recursive Length Prefix (RLP) encoding of base::Values consisting of string,
// blob, or int data
// https://ethereum.org/en/developers/docs/data-structures-and-encoding/rlp/
std::vector<uint8_t> RLPEncode(const base::Value& val);
std::vector<uint8_t> RLPEncode(const base::Value::List& val);

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_RLP_ENCODE_H_
