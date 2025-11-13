// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_TESTING_SHARD_TREE_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_TESTING_SHARD_TREE_H_

#include <memory>

#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

namespace qorai_wallet {

class OrchardStorage;

namespace orchard {

class OrchardShardTree;

// Creates a small tree height of 8 for testing purposes.
std::unique_ptr<OrchardShardTree> CreateShardTreeForTesting(  // IN-TEST
    ::qorai_wallet::OrchardStorage& storage,
    const mojom::AccountIdPtr& account_id);

}  // namespace orchard
}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_ORCHARD_TESTING_SHARD_TREE_H_
