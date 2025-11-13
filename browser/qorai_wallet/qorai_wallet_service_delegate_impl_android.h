/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_SERVICE_DELEGATE_IMPL_ANDROID_H_
#define QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_SERVICE_DELEGATE_IMPL_ANDROID_H_

#include <memory>
#include <optional>
#include <string>

#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_service_delegate_base.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"

namespace content {
class BrowserContext;
}

namespace qorai_wallet {

class ExternalWalletsImporter;

class QorAIWalletServiceDelegateImpl : public QorAIWalletServiceDelegateBase {
 public:
  explicit QorAIWalletServiceDelegateImpl(content::BrowserContext* context);
  QorAIWalletServiceDelegateImpl(const QorAIWalletServiceDelegateImpl&) =
      delete;
  QorAIWalletServiceDelegateImpl& operator=(
      const QorAIWalletServiceDelegateImpl&) = delete;
  ~QorAIWalletServiceDelegateImpl() override;

  bool AddPermission(mojom::CoinType coin,
                     const url::Origin& origin,
                     const std::string& account) override;
  void GetWebSitesWithPermission(
      mojom::CoinType coin,
      GetWebSitesWithPermissionCallback callback) override;
  void ResetWebSitePermission(mojom::CoinType coin,
                              const std::string& formed_website,
                              ResetWebSitePermissionCallback callback) override;
  std::optional<url::Origin> GetActiveOrigin() override;

 private:
  base::ObserverList<QorAIWalletServiceDelegate::Observer> observer_list_;

  base::WeakPtrFactory<QorAIWalletServiceDelegateImpl> weak_ptr_factory_;
};

}  // namespace qorai_wallet

#endif  // QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_SERVICE_DELEGATE_IMPL_ANDROID_H_
