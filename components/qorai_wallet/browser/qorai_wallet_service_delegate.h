/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_WALLET_BROWSER_QORAI_WALLET_SERVICE_DELEGATE_H_
#define QORAI_COMPONENTS_QORAI_WALLET_BROWSER_QORAI_WALLET_SERVICE_DELEGATE_H_

#include <memory>
#include <optional>
#include <string>

#include "base/functional/callback.h"
#include "base/observer_list_types.h"
#include "base/types/expected.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet_types.h"
#include "url/origin.h"

namespace content {
class BrowserContext;
}

namespace qorai_wallet {

class QoraiWalletServiceDelegate {
 public:
  using IsExternalWalletInstalledCallback = base::OnceCallback<void(bool)>;
  using IsExternalWalletInitializedCallback = base::OnceCallback<void(bool)>;
  using GetImportInfoCallback =
      base::OnceCallback<void(base::expected<ImportInfo, ImportError>)>;
  using GetWebSitesWithPermissionCallback =
      mojom::QoraiWalletService::GetWebSitesWithPermissionCallback;
  using ResetWebSitePermissionCallback =
      mojom::QoraiWalletService::ResetWebSitePermissionCallback;

  QoraiWalletServiceDelegate() = default;
  QoraiWalletServiceDelegate(const QoraiWalletServiceDelegate&) = delete;
  QoraiWalletServiceDelegate& operator=(const QoraiWalletServiceDelegate&) =
      delete;
  virtual ~QoraiWalletServiceDelegate() = default;

  class Observer : public base::CheckedObserver {
   public:
    virtual void OnActiveOriginChanged(
        const mojom::OriginInfoPtr& origin_info) {}
  };
  virtual void AddObserver(Observer* observer) {}
  virtual void RemoveObserver(Observer* observer) {}

  virtual void IsExternalWalletInstalled(mojom::ExternalWalletType,
                                         IsExternalWalletInstalledCallback);
  virtual void IsExternalWalletInitialized(mojom::ExternalWalletType,
                                           IsExternalWalletInitializedCallback);
  virtual void GetImportInfoFromExternalWallet(mojom::ExternalWalletType type,
                                               const std::string& password,
                                               GetImportInfoCallback callback);
  virtual bool AddPermission(mojom::CoinType coin,
                             const url::Origin& origin,
                             const std::string& account);
  virtual bool HasPermission(mojom::CoinType coin,
                             const url::Origin& origin,
                             const std::string& account);
  virtual bool ResetPermission(mojom::CoinType coin,
                               const url::Origin& origin,
                               const std::string& account);
  virtual bool IsPermissionDenied(mojom::CoinType coin,
                                  const url::Origin& origin);
  virtual void ResetAllPermissions() {}
  virtual void GetWebSitesWithPermission(
      mojom::CoinType coin,
      GetWebSitesWithPermissionCallback callback);
  virtual void ResetWebSitePermission(mojom::CoinType coin,
                                      const std::string& formed_website,
                                      ResetWebSitePermissionCallback callback);

  virtual std::optional<url::Origin> GetActiveOrigin();

  virtual void ClearWalletUIStoragePartition();

  virtual base::FilePath GetWalletBaseDirectory() = 0;

  virtual bool IsPrivateWindow() = 0;

  static std::unique_ptr<QoraiWalletServiceDelegate> Create(
      content::BrowserContext* browser_context);
};

}  // namespace qorai_wallet

#endif  // QORAI_COMPONENTS_QORAI_WALLET_BROWSER_QORAI_WALLET_SERVICE_DELEGATE_H_
