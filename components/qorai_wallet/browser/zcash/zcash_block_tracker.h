/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_BLOCK_TRACKER_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_BLOCK_TRACKER_H_

#include <map>
#include <optional>
#include <string>

#include "base/memory/raw_ref.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/time/time.h"
#include "base/types/expected.h"
#include "qorai/components/qorai_wallet/browser/block_tracker.h"
#include "qorai/components/services/qorai_wallet/public/mojom/zcash_decoder.mojom.h"

namespace qorai_wallet {

class ZCashRpc;

class ZCashBlockTracker : public BlockTracker {
 public:
  explicit ZCashBlockTracker(ZCashRpc& zcash_rpc);
  ~ZCashBlockTracker() override;
  ZCashBlockTracker(const ZCashBlockTracker&) = delete;
  ZCashBlockTracker operator=(const ZCashBlockTracker&) = delete;

  class Observer : public base::CheckedObserver {
   public:
    virtual void OnLatestHeightUpdated(const std::string& chain_id,
                                       uint32_t latest_height) = 0;
  };

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  void Start(const std::string& chain_id, base::TimeDelta interval) override;
  std::optional<uint32_t> GetLatestHeight(const std::string& chain_id) const;

 private:
  void GetBlockHeight(const std::string& chain_id);
  void OnGetLatestBlockForHeight(
      const std::string& chain_id,
      base::expected<zcash::mojom::BlockIDPtr, std::string> latest_height);

  // <chain_id, block_height>
  std::map<std::string, uint32_t> latest_height_map_;
  base::ObserverList<Observer> observers_;

  const raw_ref<ZCashRpc> zcash_rpc_;

  base::WeakPtrFactory<ZCashBlockTracker> weak_ptr_factory_{this};
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_BLOCK_TRACKER_H_
