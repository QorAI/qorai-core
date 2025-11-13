/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ACCOUNT_QORAI_ACCOUNT_SERVICE_FACTORY_H_
#define QORAI_BROWSER_QORAI_ACCOUNT_QORAI_ACCOUNT_SERVICE_FACTORY_H_

#include <memory>

#include "base/no_destructor.h"
#include "chrome/browser/profiles/profile_keyed_service_factory.h"

class KeyedService;

namespace content {
class BrowserContext;
}

namespace qorai_account {

class QorAIAccountService;

class QorAIAccountServiceFactory : public ProfileKeyedServiceFactory {
 public:
  QorAIAccountServiceFactory(const QorAIAccountServiceFactory&) = delete;
  QorAIAccountServiceFactory& operator=(const QorAIAccountServiceFactory&) =
      delete;

  static QorAIAccountServiceFactory* GetInstance();
  static QorAIAccountService* GetFor(content::BrowserContext* context);

 private:
  friend base::NoDestructor<QorAIAccountServiceFactory>;

  QorAIAccountServiceFactory();
  ~QorAIAccountServiceFactory() override;

  // BrowserContextKeyedServiceFactory:
  bool ServiceIsCreatedWithBrowserContext() const override;

  bool ServiceIsNULLWhileTesting() const override;

  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
};

}  // namespace qorai_account

#endif  // QORAI_BROWSER_QORAI_ACCOUNT_QORAI_ACCOUNT_SERVICE_FACTORY_H_
