/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_BLOCK_DECODER_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_BLOCK_DECODER_H_

#include <memory>
#include <optional>
#include <vector>

#include "qorai/components/qorai_wallet/browser/zcash/rust/orchard_decoded_blocks_bundle.h"
#include "qorai/components/services/qorai_wallet/public/mojom/zcash_decoder.mojom.h"

namespace qorai_wallet::orchard {

class OrchardBlockDecoder {
 public:
  static std::unique_ptr<OrchardDecodedBlocksBundle> DecodeBlocks(
      const OrchardFullViewKey& fvk,
      const ::qorai_wallet::OrchardTreeState& tree_state,
      const std::vector<::qorai_wallet::zcash::mojom::CompactBlockPtr>& blocks);

 private:
  OrchardBlockDecoder();
  ~OrchardBlockDecoder();
};

}  // namespace qorai_wallet::orchard

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_BLOCK_DECODER_H_
