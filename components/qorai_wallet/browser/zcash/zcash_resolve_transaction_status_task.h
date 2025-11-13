// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_RESOLVE_TRANSACTION_STATUS_TASK_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_RESOLVE_TRANSACTION_STATUS_TASK_H_

#include <memory>
#include <string>
#include <variant>

#include "base/functional/callback.h"
#include "qorai/components/qorai_wallet/browser/zcash/zcash_action_context.h"
#include "qorai/components/qorai_wallet/browser/zcash/zcash_wallet_service.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

namespace qorai_wallet {

class ZCashTxMeta;

// Resolves transaction status task.
// Handles tx expiry cases.
class ZCashResolveTransactionStatusTask {
 public:
  using ZCashResolveTransactionStatusTaskCallback = base::OnceCallback<void(
      base::expected<ZCashWalletService::ResolveTransactionStatusResult,
                     std::string>)>;

  ZCashResolveTransactionStatusTask(
      std::variant<base::PassKey<ZCashWalletService>,
                   base::PassKey<class ZCashResolveTransactionStatusTaskTest>>
          pass_key,
      ZCashActionContext context,
      ZCashWalletService& zcash_wallet_service,
      std::unique_ptr<ZCashTxMeta> tx_meta);
  ~ZCashResolveTransactionStatusTask();

  void Start(ZCashResolveTransactionStatusTaskCallback callback);

 private:
  void ScheduleWorkOnTask();
  void WorkOnTask();

  void GetChainTip();
  void OnGetChainTipResult(
      base::expected<zcash::mojom::BlockIDPtr, std::string> result);

  void GetTransaction();
  void OnGetTransactionResult(
      base::expected<zcash::mojom::RawTransactionPtr, std::string> result);

  ZCashActionContext context_;
  raw_ref<ZCashWalletService> zcash_wallet_service_;
  std::unique_ptr<ZCashTxMeta> tx_meta_;
  ZCashResolveTransactionStatusTaskCallback callback_;

  std::optional<std::string> error_;
  std::optional<zcash::mojom::BlockIDPtr> chain_tip_;
  std::optional<zcash::mojom::RawTransactionPtr> transaction_;

  base::WeakPtrFactory<ZCashResolveTransactionStatusTask> weak_ptr_factory_{
      this};
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_ZCASH_ZCASH_RESOLVE_TRANSACTION_STATUS_TASK_H_
