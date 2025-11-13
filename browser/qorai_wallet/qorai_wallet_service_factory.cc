/* Copyright (c) 2022 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_wallet/qorai_wallet_service_factory.h"

#include <memory>
#include <utility>

#include "base/no_destructor.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_context_utils.h"
#include "qorai/components/qorai_wallet/browser/bitcoin/bitcoin_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service_delegate.h"
#include "qorai/components/qorai_wallet/browser/json_rpc_service.h"
#include "qorai/components/qorai_wallet/browser/tx_service.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/incognito_helpers.h"
#include "chrome/browser/profiles/profile.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/user_prefs/user_prefs.h"
#include "content/public/browser/storage_partition.h"

namespace qorai_wallet {

// static
QorAIWalletServiceFactory* QorAIWalletServiceFactory::GetInstance() {
  static base::NoDestructor<QorAIWalletServiceFactory> instance;
  return instance.get();
}

// static
QorAIWalletService* QorAIWalletServiceFactory::GetServiceForContext(
    content::BrowserContext* context) {
  if (!IsAllowedForContext(context)) {
    return nullptr;
  }
  return static_cast<QorAIWalletService*>(
      GetInstance()->GetServiceForBrowserContext(context, true));
}

QorAIWalletServiceFactory::QorAIWalletServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "QorAIWalletService",
          BrowserContextDependencyManager::GetInstance()) {}

QorAIWalletServiceFactory::~QorAIWalletServiceFactory() = default;

std::unique_ptr<KeyedService>
QorAIWalletServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  return std::make_unique<QorAIWalletService>(
      context->GetDefaultStoragePartition()
          ->GetURLLoaderFactoryForBrowserProcess(),
      QorAIWalletServiceDelegate::Create(context),
      user_prefs::UserPrefs::Get(context), g_browser_process->local_state());
}

content::BrowserContext* QorAIWalletServiceFactory::GetBrowserContextToUse(
    content::BrowserContext* context) const {
  return context;
}

bool QorAIWalletServiceFactory::ServiceIsNULLWhileTesting() const {
  // KeyringService and QorAIWalletP3A expect a valid local state. Without it
  // we'd need to put a lot of unnecessary ifs/checks into those services.
  // Instead, we just won't create the wallet service if the local state isn't
  // available.
  return (g_browser_process->local_state() == nullptr);
}

}  // namespace qorai_wallet
