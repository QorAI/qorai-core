/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_RESOLVE_BALANCE_TASK_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_RESOLVE_BALANCE_TASK_H_

#include <optional>
#include <string>
#include <vector>

#include "base/memory/raw_ref.h"
#include "base/types/expected.h"
#include "qorai/components/qorai_wallet/browser/zcash/zcash_wallet_service.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/components/qorai_wallet/common/buildflags.h"
#include "qorai/components/qorai_wallet/common/zcash_utils.h"

namespace qorai_wallet {

class ZCashResolveBalanceTask {
 public:
  using ZCashResolveBalanceTaskCallback = base::OnceCallback<void(
      base::expected<mojom::ZCashBalancePtr, std::string>)>;
  ZCashResolveBalanceTask(base::PassKey<ZCashWalletService> pass_key,
                          ZCashWalletService& zcash_wallet_service,
                          ZCashActionContext context);
  ~ZCashResolveBalanceTask();

  void Start(ZCashResolveBalanceTaskCallback callback);

 private:
  void ScheduleWorkOnTask();
  void WorkOnTask();

  void OnDiscoveryDoneForBalance(
      ZCashWalletService::RunDiscoveryResult discovery_result);

  void OnUtxosResolvedForBalance(
      base::expected<ZCashWalletService::UtxoMap, std::string> result);

#if BUILDFLAG(ENABLE_ORCHARD)
  void OnGetSpendableNotes(
      base::expected<std::optional<OrchardSyncState::SpendableNotesBundle>,
                     OrchardStorage::Error> result);

#endif  // BUILDFLAG(ENABLE_ORCHARD)

  void CreateBalance();

  const raw_ref<ZCashWalletService> zcash_wallet_service_;  // Owns this
  ZCashActionContext context_;
  ZCashResolveBalanceTaskCallback callback_;

  std::optional<std::string> error_;
  std::optional<ZCashWalletService::RunDiscoveryResult> discovery_result_;
  std::optional<ZCashWalletService::UtxoMap> utxo_map_;
  std::optional<mojom::ZCashBalancePtr> result_;

#if BUILDFLAG(ENABLE_ORCHARD)
  std::optional<OrchardSyncState::SpendableNotesBundle> spendable_notes_result_;
#endif  // BUILDFLAG(ENABLE_ORCHARD)

  base::WeakPtrFactory<ZCashResolveBalanceTask> weak_ptr_factory_{this};
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_RESOLVE_BALANCE_TASK_H_
