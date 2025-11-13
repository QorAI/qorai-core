/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_TEST_UTILS_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_TEST_UTILS_H_

#include <array>
#include <vector>

#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/components/qorai_wallet/common/buildflags.h"
#include "qorai/components/qorai_wallet/common/zcash_utils.h"
#include "qorai/components/services/qorai_wallet/public/mojom/zcash_decoder.mojom.h"

#if BUILDFLAG(ENABLE_ORCHARD)
#include "qorai/components/qorai_wallet/browser/zcash/zcash_shield_sync_service.h"
#endif

namespace qorai_wallet {

#if BUILDFLAG(ENABLE_ORCHARD)
class MockOrchardBlockScannerProxy
    : public ZCashShieldSyncService::OrchardBlockScannerProxy {
 public:
  using Callback = base::RepeatingCallback<void(
      OrchardTreeState tree_state,
      std::vector<zcash::mojom::CompactBlockPtr> blocks,
      base::OnceCallback<void(base::expected<OrchardBlockScanner::Result,
                                             OrchardBlockScanner::ErrorCode>)>
          callback)>;

  explicit MockOrchardBlockScannerProxy(Callback callback);

  ~MockOrchardBlockScannerProxy() override;

  void ScanBlocks(
      OrchardTreeState tree_state,
      std::vector<zcash::mojom::CompactBlockPtr> blocks,
      base::OnceCallback<void(base::expected<OrchardBlockScanner::Result,
                                             OrchardBlockScanner::ErrorCode>)>
          callback) override;

 private:
  Callback callback_;
};
#endif

std::array<uint8_t, kOrchardNullifierSize> GenerateMockNullifier(
    const mojom::AccountIdPtr& account_id,
    uint8_t seed);
OrchardNoteSpend GenerateMockNoteSpend(const mojom::AccountIdPtr& account_id,
                                       uint32_t block_id,
                                       uint8_t seed);
OrchardNullifier GenerateMockNullifier(const mojom::AccountIdPtr& account_id,
                                       uint8_t seed);
OrchardNote GenerateMockOrchardNote(const mojom::AccountIdPtr& account_id,
                                    uint32_t block_id,
                                    uint8_t seed);
OrchardNote GenerateMockOrchardNote(const mojom::AccountIdPtr& account_id,
                                    uint32_t block_id,
                                    uint8_t seed,
                                    uint64_t value);

void SortByBlockId(std::vector<OrchardNote>& vec);

std::vector<zcash::mojom::ZCashUtxoPtr> GetZCashUtxo(uint64_t amount);

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_TEST_UTILS_H_
