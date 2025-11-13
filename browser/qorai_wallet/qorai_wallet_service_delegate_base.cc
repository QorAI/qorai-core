/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_wallet/qorai_wallet_service_delegate_base.h"

#include "qorai/components/qorai_wallet/browser/qorai_wallet_constants.h"
#include "qorai/components/qorai_wallet/browser/permission_utils.h"
#include "qorai/components/permissions/contexts/qorai_wallet_permission_context.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/browser_context.h"

namespace qorai_wallet {

QorAIWalletServiceDelegateBase::QorAIWalletServiceDelegateBase(
    content::BrowserContext* context)
    : context_(context) {
  wallet_base_directory_ = context->GetPath().AppendASCII(kWalletBaseDirectory);
  is_private_window_ =
      Profile::FromBrowserContext(context)->IsIncognitoProfile();
}

QorAIWalletServiceDelegateBase::~QorAIWalletServiceDelegateBase() = default;

bool QorAIWalletServiceDelegateBase::HasPermission(mojom::CoinType coin,
                                                   const url::Origin& origin,
                                                   const std::string& account) {
  bool has_permission = false;
  auto type = CoinTypeToPermissionType(coin);
  if (!type) {
    return false;
  }

  bool success = permissions::QorAIWalletPermissionContext::HasPermission(
      *type, context_, origin, account, &has_permission);
  return success && has_permission;
}

bool QorAIWalletServiceDelegateBase::ResetPermission(
    mojom::CoinType coin,
    const url::Origin& origin,
    const std::string& account) {
  auto type = CoinTypeToPermissionType(coin);
  if (!type) {
    return false;
  }

  return permissions::QorAIWalletPermissionContext::ResetPermission(
      *type, context_, origin, account);
}

bool QorAIWalletServiceDelegateBase::IsPermissionDenied(
    mojom::CoinType coin,
    const url::Origin& origin) {
  auto type = CoinTypeToPermissionType(coin);
  if (!type) {
    return false;
  }

  return permissions::QorAIWalletPermissionContext::IsPermissionDenied(
      *type, context_, origin);
}

void QorAIWalletServiceDelegateBase::ResetAllPermissions() {
  permissions::QorAIWalletPermissionContext::ResetAllPermissions(context_);
}

base::FilePath QorAIWalletServiceDelegateBase::GetWalletBaseDirectory() {
  return wallet_base_directory_;
}

bool QorAIWalletServiceDelegateBase::IsPrivateWindow() {
  return is_private_window_;
}

}  // namespace qorai_wallet
