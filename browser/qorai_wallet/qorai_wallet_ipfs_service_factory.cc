/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_wallet/qorai_wallet_ipfs_service_factory.h"

#include <memory>
#include <utility>

#include "base/no_destructor.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_context_utils.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/incognito_helpers.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/user_prefs/user_prefs.h"
#include "content/public/browser/storage_partition.h"

namespace qorai_wallet {

// static
QorAIWalletIpfsServiceFactory* QorAIWalletIpfsServiceFactory::GetInstance() {
  static base::NoDestructor<QorAIWalletIpfsServiceFactory> instance;
  return instance.get();
}

// static
mojo::PendingRemote<mojom::IpfsService>
QorAIWalletIpfsServiceFactory::GetForContext(content::BrowserContext* context) {
  if (!IsAllowedForContext(context)) {
    return mojo::PendingRemote<mojom::IpfsService>();
  }

  return static_cast<QorAIWalletIpfsService*>(
             GetInstance()->GetServiceForBrowserContext(context, true))
      ->MakeRemote();
}

// static
QorAIWalletIpfsService* QorAIWalletIpfsServiceFactory::GetServiceForContext(
    content::BrowserContext* context) {
  if (!IsAllowedForContext(context)) {
    return nullptr;
  }
  return static_cast<QorAIWalletIpfsService*>(
      GetInstance()->GetServiceForBrowserContext(context, true));
}

// static
void QorAIWalletIpfsServiceFactory::BindForContext(
    content::BrowserContext* context,
    mojo::PendingReceiver<mojom::IpfsService> receiver) {
  auto* ipfs_service =
      QorAIWalletIpfsServiceFactory::GetServiceForContext(context);
  if (ipfs_service) {
    ipfs_service->Bind(std::move(receiver));
  }
}

QorAIWalletIpfsServiceFactory::QorAIWalletIpfsServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "QorAIWalletIpfsService",
          BrowserContextDependencyManager::GetInstance()) {}

QorAIWalletIpfsServiceFactory::~QorAIWalletIpfsServiceFactory() = default;

std::unique_ptr<KeyedService>
QorAIWalletIpfsServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  return std::make_unique<QorAIWalletIpfsService>(
      user_prefs::UserPrefs::Get(context));
}

content::BrowserContext* QorAIWalletIpfsServiceFactory::GetBrowserContextToUse(
    content::BrowserContext* context) const {
  return GetBrowserContextRedirectedInIncognito(context);
}

}  // namespace qorai_wallet
