/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/components/qorai_wallet/browser/qorai_wallet_service_delegate.h"

#include <optional>
#include <utility>
#include <vector>

#include "base/notimplemented.h"
#include "base/types/expected.h"

namespace qorai_wallet {

void QoraiWalletServiceDelegate::IsExternalWalletInstalled(
    mojom::ExternalWalletType type,
    IsExternalWalletInstalledCallback callback) {
  NOTIMPLEMENTED();
  std::move(callback).Run(false);
}

void QoraiWalletServiceDelegate::IsExternalWalletInitialized(
    mojom::ExternalWalletType type,
    IsExternalWalletInitializedCallback callback) {
  NOTIMPLEMENTED();
  std::move(callback).Run(false);
}

void QoraiWalletServiceDelegate::GetImportInfoFromExternalWallet(
    mojom::ExternalWalletType type,
    const std::string& password,
    GetImportInfoCallback callback) {
  NOTIMPLEMENTED();
  std::move(callback).Run(base::unexpected(ImportError::kInternalError));
}

bool QoraiWalletServiceDelegate::AddPermission(mojom::CoinType coin,
                                               const url::Origin& origin,
                                               const std::string& account) {
  NOTIMPLEMENTED();
  return false;
}

bool QoraiWalletServiceDelegate::HasPermission(mojom::CoinType coin,
                                               const url::Origin& origin,
                                               const std::string& account) {
  NOTIMPLEMENTED();
  return false;
}

bool QoraiWalletServiceDelegate::ResetPermission(mojom::CoinType coin,
                                                 const url::Origin& origin,
                                                 const std::string& account) {
  NOTIMPLEMENTED();
  return false;
}

bool QoraiWalletServiceDelegate::IsPermissionDenied(mojom::CoinType coin,
                                                    const url::Origin& origin) {
  NOTIMPLEMENTED();
  return false;
}

std::optional<url::Origin> QoraiWalletServiceDelegate::GetActiveOrigin() {
  NOTIMPLEMENTED();
  return std::nullopt;
}

void QoraiWalletServiceDelegate::ClearWalletUIStoragePartition() {}

void QoraiWalletServiceDelegate::GetWebSitesWithPermission(
    mojom::CoinType coin,
    GetWebSitesWithPermissionCallback callback) {
  NOTIMPLEMENTED();
  std::move(callback).Run(std::vector<std::string>());
}

void QoraiWalletServiceDelegate::ResetWebSitePermission(
    mojom::CoinType coin,
    const std::string& formed_website,
    ResetWebSitePermissionCallback callback) {
  NOTIMPLEMENTED();
  std::move(callback).Run(false);
}

}  // namespace qorai_wallet
