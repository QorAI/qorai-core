/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_wallet/qorai_wallet_service_delegate_impl_android.h"

#include <algorithm>
#include <optional>
#include <utility>
#include <vector>

#include "base/check_op.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_utils.h"
#include "qorai/components/qorai_wallet/browser/permission_utils.h"
#include "qorai/components/permissions/contexts/qorai_wallet_permission_context.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/android/tab_model/tab_model.h"
#include "chrome/browser/ui/android/tab_model/tab_model_list.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/web_contents.h"

namespace qorai_wallet {

namespace {
content::WebContents* GetActiveWebContents(content::BrowserContext* context) {
  auto tab_models = TabModelList::models();
  auto iter = std::ranges::find_if(
      tab_models, [](const auto& model) { return model->IsActiveModel(); });
  if (iter == tab_models.end()) {
    return nullptr;
  }

  auto* active_contents = (*iter)->GetActiveWebContents();
  if (!active_contents) {
    return nullptr;
  }
  DCHECK_EQ(active_contents->GetBrowserContext(), context);
  return active_contents;
}
}  // namespace

QorAIWalletServiceDelegateImpl::QorAIWalletServiceDelegateImpl(
    content::BrowserContext* context)
    : QorAIWalletServiceDelegateBase(context), weak_ptr_factory_(this) {}

QorAIWalletServiceDelegateImpl::~QorAIWalletServiceDelegateImpl() = default;

bool QorAIWalletServiceDelegateImpl::AddPermission(mojom::CoinType coin,
                                                   const url::Origin& origin,
                                                   const std::string& account) {
  auto type = CoinTypeToPermissionType(coin);
  if (!type) {
    return false;
  }

  return permissions::QorAIWalletPermissionContext::AddPermission(
      *type, context_, origin, account);
}

void QorAIWalletServiceDelegateImpl::GetWebSitesWithPermission(
    mojom::CoinType coin,
    GetWebSitesWithPermissionCallback callback) {
  auto type = CoinTypeToPermissionType(coin);
  if (!type) {
    std::move(callback).Run({});
    return;
  }
  std::move(callback).Run(
      permissions::QorAIWalletPermissionContext::GetWebSitesWithPermission(
          *type, context_));
}

void QorAIWalletServiceDelegateImpl::ResetWebSitePermission(
    mojom::CoinType coin,
    const std::string& formed_website,
    ResetWebSitePermissionCallback callback) {
  auto type = CoinTypeToPermissionType(coin);
  if (!type) {
    std::move(callback).Run(false);
    return;
  }
  std::move(callback).Run(
      permissions::QorAIWalletPermissionContext::ResetWebSitePermission(
          *type, context_, formed_website));
}

std::optional<url::Origin> QorAIWalletServiceDelegateImpl::GetActiveOrigin() {
  content::WebContents* contents = GetActiveWebContents(context_);
  auto origin = contents
                    ? contents->GetPrimaryMainFrame()->GetLastCommittedOrigin()
                    : std::optional<url::Origin>();
  return origin;
}

}  // namespace qorai_wallet
