/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_wallet/qorai_wallet_service_delegate_impl.h"

#include <optional>
#include <utility>

#include "base/check.h"
#include "base/types/expected.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_utils.h"
#include "qorai/components/qorai_wallet/browser/permission_utils.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "qorai/components/permissions/contexts/qorai_wallet_permission_context.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/tabs/tab_strip_model.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/storage_partition.h"
#include "content/public/browser/web_contents.h"
#include "url/gurl.h"
#include "url/origin.h"

using content::StoragePartition;

namespace qorai_wallet {

namespace {

content::WebContents* g_web_contents_for_testing = nullptr;

content::WebContents* GetActiveWebContents() {
  if (g_web_contents_for_testing) {
    return g_web_contents_for_testing;
  }

  Browser* browser = chrome::FindLastActive();
  return browser ? browser->tab_strip_model()->GetActiveWebContents() : nullptr;
}

void ClearWalletStoragePartition(content::BrowserContext* context,
                                 const GURL& url) {
  CHECK(context);
  auto* partition = context->GetDefaultStoragePartition();
  partition->ClearDataForOrigin(
      StoragePartition::REMOVE_DATA_MASK_ALL,
      StoragePartition::QUOTA_MANAGED_STORAGE_MASK_ALL, url, base::DoNothing());
}

}  // namespace

QorAIWalletServiceDelegateImpl::QorAIWalletServiceDelegateImpl(
    content::BrowserContext* context)
    : QorAIWalletServiceDelegateBase(context),
      browser_tab_strip_tracker_(this, this),
      weak_ptr_factory_(this) {
  browser_tab_strip_tracker_.Init();
}

QorAIWalletServiceDelegateImpl::~QorAIWalletServiceDelegateImpl() = default;

// static
void QorAIWalletServiceDelegateImpl::SetActiveWebContentsForTesting(
    content::WebContents* web_contents) {
  g_web_contents_for_testing = web_contents;
}

void QorAIWalletServiceDelegateImpl::AddObserver(
    QorAIWalletServiceDelegate::Observer* observer) {
  observer_list_.AddObserver(observer);
}

void QorAIWalletServiceDelegateImpl::RemoveObserver(
    QorAIWalletServiceDelegate::Observer* observer) {
  observer_list_.RemoveObserver(observer);
}

bool QorAIWalletServiceDelegateImpl::ShouldTrackBrowser(
    BrowserWindowInterface* browser) {
  return browser->GetProfile() == Profile::FromBrowserContext(context_);
}

void QorAIWalletServiceDelegateImpl::IsExternalWalletInstalled(
    mojom::ExternalWalletType type,
    IsExternalWalletInstalledCallback callback) {
  ExternalWalletsImporter importer(type, context_);
  std::move(callback).Run(importer.IsExternalWalletInstalled());
}

void QorAIWalletServiceDelegateImpl::IsExternalWalletInitialized(
    mojom::ExternalWalletType type,
    IsExternalWalletInitializedCallback callback) {
  importers_[type] = std::make_unique<ExternalWalletsImporter>(type, context_);
  // Do not try to init the importer when external wallet is not installed
  if (!importers_[type]->IsExternalWalletInstalled()) {
    std::move(callback).Run(false);
    return;
  }
  if (importers_[type]->IsInitialized()) {
    ContinueIsExternalWalletInitialized(type, std::move(callback), true);
  } else {
    importers_[type]->Initialize(base::BindOnce(
        &QorAIWalletServiceDelegateImpl::ContinueIsExternalWalletInitialized,
        weak_ptr_factory_.GetWeakPtr(), type, std::move(callback)));
  }
}

void QorAIWalletServiceDelegateImpl::ContinueIsExternalWalletInitialized(
    mojom::ExternalWalletType type,
    IsExternalWalletInitializedCallback callback,
    bool init_success) {
  DCHECK(importers_[type]);
  if (init_success) {
    std::move(callback).Run(importers_[type]->IsExternalWalletInitialized());
  } else {
    std::move(callback).Run(false);
  }
}

void QorAIWalletServiceDelegateImpl::GetImportInfoFromExternalWallet(
    mojom::ExternalWalletType type,
    const std::string& password,
    GetImportInfoCallback callback) {
  if (!importers_[type]) {
    importers_[type] =
        std::make_unique<ExternalWalletsImporter>(type, context_);
  }
  if (importers_[type]->IsInitialized()) {
    ContinueGetImportInfoFromExternalWallet(type, password, std::move(callback),
                                            true);
  } else {
    importers_[type]->Initialize(base::BindOnce(
        &QorAIWalletServiceDelegateImpl::
            ContinueGetImportInfoFromExternalWallet,
        weak_ptr_factory_.GetWeakPtr(), type, password, std::move(callback)));
  }
}

void QorAIWalletServiceDelegateImpl::ContinueGetImportInfoFromExternalWallet(
    mojom::ExternalWalletType type,
    const std::string& password,
    GetImportInfoCallback callback,
    bool init_success) {
  DCHECK(importers_[type]);
  if (init_success) {
    DCHECK(importers_[type]->IsInitialized());
    importers_[type]->GetImportInfo(password, std::move(callback));
  } else {
    std::move(callback).Run(base::unexpected(ImportError::kInternalError));
  }
}

void QorAIWalletServiceDelegateImpl::OnTabStripModelChanged(
    TabStripModel* tab_strip_model,
    const TabStripModelChange& change,
    const TabStripSelectionChange& selection) {
  FireActiveOriginChanged();
}

void QorAIWalletServiceDelegateImpl::TabChangedAt(
    content::WebContents* contents,
    int index,
    TabChangeType change_type) {
  if (!contents || contents != GetActiveWebContents()) {
    return;
  }

  FireActiveOriginChanged();
}

void QorAIWalletServiceDelegateImpl::FireActiveOriginChanged() {
  mojom::OriginInfoPtr origin_info =
      MakeOriginInfo(GetActiveOriginInternal().value_or(url::Origin()));
  for (auto& observer : observer_list_) {
    observer.OnActiveOriginChanged(origin_info);
  }
}

std::optional<url::Origin>
QorAIWalletServiceDelegateImpl::GetActiveOriginInternal() {
  content::WebContents* contents = GetActiveWebContents();
  return contents ? contents->GetPrimaryMainFrame()->GetLastCommittedOrigin()
                  : std::optional<url::Origin>();
}

std::optional<url::Origin> QorAIWalletServiceDelegateImpl::GetActiveOrigin() {
  return GetActiveOriginInternal();
}

void QorAIWalletServiceDelegateImpl::ClearWalletUIStoragePartition() {
  ClearWalletStoragePartition(context_, GURL(kQorAIUIWalletURL));
  ClearWalletStoragePartition(context_, GURL(kQorAIUIWalletPanelURL));
}

}  // namespace qorai_wallet
