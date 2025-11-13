/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_ACTION_CONTEXT_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_ACTION_CONTEXT_H_

#include <string>

#include "base/memory/raw_ref.h"
#include "base/threading/sequence_bound.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/components/qorai_wallet/common/buildflags.h"
#include "qorai/components/qorai_wallet/common/zcash_utils.h"

namespace qorai_wallet {

class OrchardSyncState;
class ZCashRpc;

// Basic context required by most orchard-related operations.
struct ZCashActionContext {
  ZCashActionContext(
      ZCashRpc& zcash_rpc,
#if BUILDFLAG(ENABLE_ORCHARD)
      const std::optional<OrchardAddrRawPart>& account_internal_addr,
      base::SequenceBound<OrchardSyncState>& sync_state,
#endif  // BUILDFLAG(ENABLE_ORCHARD)
      const mojom::AccountIdPtr& account_id);
  ~ZCashActionContext();
  raw_ref<ZCashRpc> zcash_rpc;
#if BUILDFLAG(ENABLE_ORCHARD)
  std::optional<OrchardAddrRawPart> account_internal_addr;
  raw_ref<base::SequenceBound<OrchardSyncState>> sync_state;
#endif  // BUILDFLAG(ENABLE_ORCHARD)
  ZCashActionContext(ZCashActionContext&) = delete;
  ZCashActionContext& operator=(ZCashActionContext&) = delete;
  ZCashActionContext& operator=(ZCashActionContext&&);
  ZCashActionContext(ZCashActionContext&&);
  mojom::AccountIdPtr account_id;
  std::string chain_id;
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_ACTION_CONTEXT_H_
