// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_CXX_ORCHARD_SHARD_TREE_DELEGATE_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_CXX_ORCHARD_SHARD_TREE_DELEGATE_H_

#include "base/memory/raw_ref.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "third_party/rust/cxx/v1/cxx.h"

namespace qorai_wallet {

class OrchardStorage;

namespace orchard {

struct CxxOrchardShard;
struct CxxOrchardShardTreeCap;
struct CxxOrchardShardAddress;
struct CxxOrchardCheckpoint;

struct CxxBoolResultWrapper;
struct CxxCheckpointBundleResultWrapper;
struct CxxCheckpointCountResultWrapper;
struct CxxCheckpointIdResultWrapper;
struct CxxCheckpointsResultWrapper;
struct CxxOrchardShardResultWrapper;
struct CxxOrchardShardTreeCapResultWrapper;
struct CxxShardRootsResultWrapper;

class CxxOrchardShardTreeDelegate {
 public:
  explicit CxxOrchardShardTreeDelegate(OrchardStorage& storage,
                                       const mojom::AccountIdPtr& account_id);
  ~CxxOrchardShardTreeDelegate();

  ::rust::Box<CxxOrchardShardResultWrapper> LastShard(
      uint8_t shard_level) const;
  ::rust::Box<CxxBoolResultWrapper> PutShard(const CxxOrchardShard& tree) const;
  ::rust::Box<CxxOrchardShardResultWrapper> GetShard(
      const CxxOrchardShardAddress& addr) const;
  ::rust::Box<CxxShardRootsResultWrapper> GetShardRoots(
      uint8_t shard_level) const;
  ::rust::Box<CxxBoolResultWrapper> Truncate(
      const CxxOrchardShardAddress& address) const;
  ::rust::Box<CxxOrchardShardTreeCapResultWrapper> GetCap() const;
  ::rust::Box<CxxBoolResultWrapper> PutCap(
      const CxxOrchardShardTreeCap& tree) const;
  ::rust::Box<CxxCheckpointIdResultWrapper> MinCheckpointId() const;
  ::rust::Box<CxxCheckpointIdResultWrapper> MaxCheckpointId() const;
  ::rust::Box<CxxBoolResultWrapper> AddCheckpoint(
      uint32_t checkpoint_id,
      const CxxOrchardCheckpoint& checkpoint) const;
  ::rust::Box<CxxCheckpointCountResultWrapper> CheckpointCount() const;
  ::rust::Box<CxxCheckpointBundleResultWrapper> CheckpointAtDepth(
      size_t depth) const;
  ::rust::Box<CxxCheckpointBundleResultWrapper> GetCheckpoint(
      uint32_t checkpoint_id) const;
  ::rust::Box<CxxBoolResultWrapper> UpdateCheckpoint(
      uint32_t checkpoint_id,
      const CxxOrchardCheckpoint& checkpoint) const;
  ::rust::Box<CxxBoolResultWrapper> RemoveCheckpoint(
      uint32_t checkpoint_id) const;
  ::rust::Box<CxxBoolResultWrapper> TruncateCheckpoint(
      uint32_t checkpoint_id) const;
  ::rust::Box<CxxCheckpointsResultWrapper> GetCheckpoints(size_t limit) const;

 private:
  raw_ref<OrchardStorage> storage_;
  ::qorai_wallet::mojom::AccountIdPtr account_id_;
};

}  // namespace orchard
}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_RUST_CXX_ORCHARD_SHARD_TREE_DELEGATE_H_
