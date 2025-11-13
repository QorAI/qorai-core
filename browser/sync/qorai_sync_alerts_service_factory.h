/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_SYNC_QORAI_SYNC_ALERTS_SERVICE_FACTORY_H_
#define QORAI_BROWSER_SYNC_QORAI_SYNC_ALERTS_SERVICE_FACTORY_H_

#include <memory>

#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

class QoraiSyncAlertsService;

class QoraiSyncAlertsServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  QoraiSyncAlertsServiceFactory(const QoraiSyncAlertsServiceFactory&) = delete;
  QoraiSyncAlertsServiceFactory& operator=(
      const QoraiSyncAlertsServiceFactory&) = delete;

  static QoraiSyncAlertsService* GetForBrowserContext(
      content::BrowserContext* context);

  static QoraiSyncAlertsServiceFactory* GetInstance();

 private:
  friend base::NoDestructor<QoraiSyncAlertsServiceFactory>;

  QoraiSyncAlertsServiceFactory();
  ~QoraiSyncAlertsServiceFactory() override;

  // BrowserContextKeyedServiceFactory:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
  content::BrowserContext* GetBrowserContextToUse(
      content::BrowserContext* context) const override;
  bool ServiceIsCreatedWithBrowserContext() const override;
  bool ServiceIsNULLWhileTesting() const override;
};

#endif  // QORAI_BROWSER_SYNC_QORAI_SYNC_ALERTS_SERVICE_FACTORY_H_
