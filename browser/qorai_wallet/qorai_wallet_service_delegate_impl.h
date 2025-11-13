/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_SERVICE_DELEGATE_IMPL_H_
#define QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_SERVICE_DELEGATE_IMPL_H_

#include <memory>
#include <optional>
#include <string>

#include "base/containers/flat_map.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_service_delegate_base.h"
#include "qorai/browser/qorai_wallet/external_wallets_importer.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service_delegate.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "chrome/browser/ui/browser_tab_strip_tracker.h"
#include "chrome/browser/ui/browser_tab_strip_tracker_delegate.h"
#include "chrome/browser/ui/tabs/tab_strip_model_observer.h"

namespace content {
class BrowserContext;
class WebContents;
}  // namespace content

namespace qorai_wallet {

class QorAIWalletServiceDelegateImpl : public QorAIWalletServiceDelegateBase,
                                       public TabStripModelObserver,
                                       public BrowserTabStripTrackerDelegate {
 public:
  explicit QorAIWalletServiceDelegateImpl(content::BrowserContext* context);
  QorAIWalletServiceDelegateImpl(const QorAIWalletServiceDelegateImpl&) =
      delete;
  QorAIWalletServiceDelegateImpl& operator=(
      const QorAIWalletServiceDelegateImpl&) = delete;
  ~QorAIWalletServiceDelegateImpl() override;

  static void SetActiveWebContentsForTesting(
      content::WebContents* web_contents);

  void IsExternalWalletInstalled(mojom::ExternalWalletType,
                                 IsExternalWalletInstalledCallback) override;
  void IsExternalWalletInitialized(
      mojom::ExternalWalletType,
      IsExternalWalletInitializedCallback) override;
  void GetImportInfoFromExternalWallet(mojom::ExternalWalletType type,
                                       const std::string& password,
                                       GetImportInfoCallback callback) override;

  std::optional<url::Origin> GetActiveOrigin() override;

  void ClearWalletUIStoragePartition() override;

  void AddObserver(QorAIWalletServiceDelegate::Observer* observer) override;
  void RemoveObserver(QorAIWalletServiceDelegate::Observer* observer) override;

  // TabStripModelObserver:
  void OnTabStripModelChanged(
      TabStripModel* tab_strip_model,
      const TabStripModelChange& change,
      const TabStripSelectionChange& selection) override;
  void TabChangedAt(content::WebContents* contents,
                    int index,
                    TabChangeType change_type) override;

  // BrowserTabStripTrackerDelegate:
  bool ShouldTrackBrowser(BrowserWindowInterface* browser) override;

 private:
  friend class QorAIWalletServiceDelegateImplUnitTest;

  void ContinueIsExternalWalletInitialized(mojom::ExternalWalletType type,
                                           IsExternalWalletInitializedCallback,
                                           bool init_success);
  void ContinueGetImportInfoFromExternalWallet(mojom::ExternalWalletType type,
                                               const std::string& password,
                                               GetImportInfoCallback callback,
                                               bool init_success);

  std::optional<url::Origin> GetActiveOriginInternal();
  void FireActiveOriginChanged();

  base::flat_map<mojom::ExternalWalletType,
                 std::unique_ptr<ExternalWalletsImporter>>
      importers_;

  BrowserTabStripTracker browser_tab_strip_tracker_;
  base::ObserverList<QorAIWalletServiceDelegate::Observer> observer_list_;

  base::WeakPtrFactory<QorAIWalletServiceDelegateImpl> weak_ptr_factory_;
};

}  // namespace qorai_wallet

#endif  // QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_SERVICE_DELEGATE_IMPL_H_
