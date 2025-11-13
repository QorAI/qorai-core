/* Copyright (c) 2021 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_SERVICE_FACTORY_H_
#define QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_SERVICE_FACTORY_H_

#include <memory>

#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/browser_context.h"

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace qorai_wallet {

class QorAIWalletService;
class JsonRpcService;

class QorAIWalletServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  static QorAIWalletService* GetServiceForContext(
      content::BrowserContext* context);
  static QorAIWalletServiceFactory* GetInstance();

 private:
  friend base::NoDestructor<QorAIWalletServiceFactory>;

  QorAIWalletServiceFactory();
  ~QorAIWalletServiceFactory() override;

  QorAIWalletServiceFactory(const QorAIWalletServiceFactory&) = delete;
  QorAIWalletServiceFactory& operator=(const QorAIWalletServiceFactory&) =
      delete;

  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
  content::BrowserContext* GetBrowserContextToUse(
      content::BrowserContext* context) const override;
  bool ServiceIsNULLWhileTesting() const override;
};

}  // namespace qorai_wallet

#endif  // QORAI_BROWSER_QORAI_WALLET_QORAI_WALLET_SERVICE_FACTORY_H_
