// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_TEST_UTILS_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_TEST_UTILS_H_

#include <memory>

#include "qorai/components/qorai_wallet/browser/internal/orchard_storage/orchard_shard_tree_types.h"

namespace qorai_wallet::orchard {

class OrchardDecodedBlocksBundle;

// Builder is used in tests to create OrchardDecodedBlocksBundle with mocked
// commitments
class TestingDecodedBundleBuilder {
 public:
  TestingDecodedBundleBuilder() = default;
  virtual ~TestingDecodedBundleBuilder() = default;
  virtual void AddCommitment(::qorai_wallet::OrchardCommitment commitment) = 0;
  virtual void SetPriorTreeState(
      ::qorai_wallet::OrchardTreeState tree_state) = 0;
  virtual std::unique_ptr<OrchardDecodedBlocksBundle> Complete() = 0;
};

std::unique_ptr<TestingDecodedBundleBuilder>
CreateTestingDecodedBundleBuilder();

OrchardCommitmentValue CreateMockCommitmentValue(uint32_t position,
                                                 uint32_t rseed);

}  // namespace qorai_wallet::orchard

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_TEST_UTILS_H_
