/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/sync/qorai_sync_alerts_service_factory.h"

#include <memory>

#include "base/no_destructor.h"
#include "qorai/browser/sync/qorai_sync_alerts_service.h"
#include "chrome/browser/profiles/incognito_helpers.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/sync/sync_service_factory.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/pref_registry/pref_registry_syncable.h"

// static
QoraiSyncAlertsService* QoraiSyncAlertsServiceFactory::GetForBrowserContext(
    content::BrowserContext* context) {
  return static_cast<QoraiSyncAlertsService*>(
      GetInstance()->GetServiceForBrowserContext(context, true));
}

// static
QoraiSyncAlertsServiceFactory* QoraiSyncAlertsServiceFactory::GetInstance() {
  static base::NoDestructor<QoraiSyncAlertsServiceFactory> instance;
  return instance.get();
}

QoraiSyncAlertsServiceFactory::QoraiSyncAlertsServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "QoraiSyncAlertsService",
          BrowserContextDependencyManager::GetInstance()) {
  DependsOn(SyncServiceFactory::GetInstance());
}

QoraiSyncAlertsServiceFactory::~QoraiSyncAlertsServiceFactory() {}

std::unique_ptr<KeyedService>
QoraiSyncAlertsServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  return std::make_unique<QoraiSyncAlertsService>(
      Profile::FromBrowserContext(context));
}

content::BrowserContext* QoraiSyncAlertsServiceFactory::GetBrowserContextToUse(
    content::BrowserContext* context) const {
  return GetBrowserContextRedirectedInIncognito(context);
}

bool QoraiSyncAlertsServiceFactory::ServiceIsCreatedWithBrowserContext() const {
  return true;
}

bool QoraiSyncAlertsServiceFactory::ServiceIsNULLWhileTesting() const {
  return true;
}
