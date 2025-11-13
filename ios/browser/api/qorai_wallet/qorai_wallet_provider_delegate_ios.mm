/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/ios/browser/api/qorai_wallet/qorai_wallet_provider_delegate_ios.h"

#include <optional>

#include "base/strings/sys_string_conversions.h"
#include "qorai/base/apple/foundation_util.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/ios/browser/api/qorai_wallet/qorai_wallet_provider_delegate_ios+private.h"
#include "qorai/ios/browser/api/url/url_origin_ios+private.h"
#include "net/base/apple/url_conversions.h"

namespace qorai_wallet {

bool QoraiWalletProviderDelegateBridge::IsTabVisible() {
  return [bridge_ isTabVisible];
}

void QoraiWalletProviderDelegateBridge::ShowPanel() {
  [bridge_ showPanel];
}

void QoraiWalletProviderDelegateBridge::WalletInteractionDetected() {
  [bridge_ walletInteractionDetected];
}

url::Origin QoraiWalletProviderDelegateBridge::GetOrigin() const {
  return url::Origin([[bridge_ getOrigin] underlyingOrigin]);
}

void QoraiWalletProviderDelegateBridge::ShowWalletOnboarding() {
  [bridge_ showWalletOnboarding];
}

void QoraiWalletProviderDelegateBridge::ShowWalletBackup() {
  [bridge_ showWalletBackup];
}

void QoraiWalletProviderDelegateBridge::UnlockWallet() {
  [bridge_ unlockWallet];
}

void QoraiWalletProviderDelegateBridge::ShowAccountCreation(
    mojom::CoinType type) {
  [bridge_ showAccountCreation:static_cast<QoraiWalletCoinType>(type)];
}

void QoraiWalletProviderDelegateBridge::RequestPermissions(
    mojom::CoinType type,
    const std::vector<std::string>& accounts,
    RequestPermissionsCallback callback) {
  auto completion = [callback = std::make_shared<decltype(callback)>(std::move(
                         callback))](QoraiWalletRequestPermissionsError error,
                                     NSArray<NSString*>* _Nullable results) {
    if (!callback) {
      return;
    }
    if (results == nil) {
      std::move(*callback).Run(
          static_cast<mojom::RequestPermissionsError>(error), std::nullopt);
      return;
    }
    std::vector<std::string> v;
    for (NSString* result in results) {
      v.push_back(base::SysNSStringToUTF8(result));
    }
    std::move(*callback).Run(static_cast<mojom::RequestPermissionsError>(error),
                             v);
  };
  [bridge_ requestPermissions:static_cast<QoraiWalletCoinType>(type)
                     accounts:qorai::vector_to_ns(accounts)
                   completion:completion];
}

bool QoraiWalletProviderDelegateBridge::IsAccountAllowed(
    mojom::CoinType type,
    const std::string& account) {
  return [bridge_ isAccountAllowed:static_cast<QoraiWalletCoinType>(type)
                           account:base::SysUTF8ToNSString(account)];
}

std::optional<std::vector<std::string>>
QoraiWalletProviderDelegateBridge::GetAllowedAccounts(
    mojom::CoinType type,
    const std::vector<std::string>& accounts) {
  NSArray<NSString*>* results =
      [bridge_ getAllowedAccounts:static_cast<QoraiWalletCoinType>(type)
                         accounts:qorai::vector_to_ns(accounts)];
  if (!results) {
    return std::nullopt;
  }

  return qorai::ns_to_vector<std::string>(results);
}

bool QoraiWalletProviderDelegateBridge::IsPermissionDenied(
    mojom::CoinType type) {
  return [bridge_ isPermissionDenied:static_cast<QoraiWalletCoinType>(type)];
}

void QoraiWalletProviderDelegateBridge::AddSolanaConnectedAccount(
    const std::string& account) {
  [bridge_ addSolanaConnectedAccount:base::SysUTF8ToNSString(account)];
}

void QoraiWalletProviderDelegateBridge::RemoveSolanaConnectedAccount(
    const std::string& account) {
  [bridge_ removeSolanaConnectedAccount:base::SysUTF8ToNSString(account)];
}

bool QoraiWalletProviderDelegateBridge::IsSolanaAccountConnected(
    const std::string& account) {
  return [bridge_ isSolanaAccountConnected:base::SysUTF8ToNSString(account)];
}

}  // namespace qorai_wallet
