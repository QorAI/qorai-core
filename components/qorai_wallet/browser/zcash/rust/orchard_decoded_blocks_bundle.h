// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_DECODED_BLOCKS_BUNDLE_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_DECODED_BLOCKS_BUNDLE_H_

#include <memory>
#include <vector>

#include "qorai/components/qorai_wallet/browser/internal/orchard_storage/orchard_shard_tree_types.h"

namespace qorai_wallet::orchard {

// Contains result of the batch block decoding.
// This includes Orchard leafs to be inserterted to the shard tree and
// a set of dicovered Orchard spendable notes.
class OrchardDecodedBlocksBundle {
 public:
  virtual ~OrchardDecodedBlocksBundle() = default;
  virtual std::optional<std::vector<::qorai_wallet::OrchardNote>>
  GetDiscoveredNotes() = 0;
};

}  // namespace qorai_wallet::orchard

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_DECODED_BLOCKS_BUNDLE_H_
