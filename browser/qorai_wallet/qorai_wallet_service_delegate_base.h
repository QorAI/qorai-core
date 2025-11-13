/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_SERVICE_DELEGATE_BASE_H_
#define QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_SERVICE_DELEGATE_BASE_H_

#include <string>

#include "base/memory/raw_ptr.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service_delegate.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

namespace content {
class BrowserContext;
}

namespace url {
class Origin;
}

namespace qorai_wallet {

// Shared QorAIWalletServiceDelegate implementation between Desktop and Android.
class QorAIWalletServiceDelegateBase : public QorAIWalletServiceDelegate {
 public:
  explicit QorAIWalletServiceDelegateBase(content::BrowserContext* context);
  QorAIWalletServiceDelegateBase(const QorAIWalletServiceDelegateBase&) =
      delete;
  QorAIWalletServiceDelegateBase& operator=(
      const QorAIWalletServiceDelegateBase&) = delete;
  ~QorAIWalletServiceDelegateBase() override;

  bool HasPermission(mojom::CoinType coin,
                     const url::Origin& origin,
                     const std::string& account) override;
  bool ResetPermission(mojom::CoinType coin,
                       const url::Origin& origin,
                       const std::string& account) override;
  bool IsPermissionDenied(mojom::CoinType coin,
                          const url::Origin& origin) override;
  void ResetAllPermissions() override;

  base::FilePath GetWalletBaseDirectory() override;
  bool IsPrivateWindow() override;

 protected:
  base::FilePath wallet_base_directory_;
  bool is_private_window_ = false;
  raw_ptr<content::BrowserContext> context_ = nullptr;
};

}  // namespace qorai_wallet

#endif  // QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_SERVICE_DELEGATE_BASE_H_
