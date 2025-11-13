// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_DECODED_BLOCKS_BUNDLE_IMPL_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_DECODED_BLOCKS_BUNDLE_IMPL_H_

#include <variant>
#include <vector>

#include "base/types/pass_key.h"
#include "qorai/components/qorai_wallet/browser/zcash/rust/orchard_decoded_blocks_bundle.h"
#include "third_party/rust/cxx/v1/cxx.h"

namespace qorai_wallet::orchard {

struct CxxOrchardDecodedBlocksBundle;

class OrchardDecodedBlocksBundleImpl : public OrchardDecodedBlocksBundle {
 public:
  ~OrchardDecodedBlocksBundleImpl() override;
  OrchardDecodedBlocksBundleImpl(
      std::variant<base::PassKey<class OrchardBlockDecoder>,
                   base::PassKey<class TestingDecodedBundleBuilderImpl>>,
      ::rust::Box<CxxOrchardDecodedBlocksBundle>);

  std::optional<std::vector<::qorai_wallet::OrchardNote>> GetDiscoveredNotes()
      override;
  CxxOrchardDecodedBlocksBundle& GetDecodeBundle();

 private:
  ::rust::Box<CxxOrchardDecodedBlocksBundle> cxx_orchard_decoded_blocks_bundle_;
};

}  // namespace qorai_wallet::orchard

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_DECODED_BLOCKS_BUNDLE_IMPL_H_
