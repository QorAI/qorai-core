/* Copyright (c) 2025 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/qorai_account/qorai_account_service_factory.h"

#include "qorai/components/qorai_account/qorai_account_service.h"
#include "qorai/components/qorai_account/features.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/storage_partition.h"

namespace qorai_account {

// static
QorAIAccountServiceFactory* QorAIAccountServiceFactory::GetInstance() {
  static base::NoDestructor<QorAIAccountServiceFactory> instance;
  return instance.get();
}

// static
QorAIAccountService* QorAIAccountServiceFactory::GetFor(
    content::BrowserContext* context) {
  CHECK(context);
  return static_cast<QorAIAccountService*>(
      GetInstance()->GetServiceForContext(context, true));
}

QorAIAccountServiceFactory::QorAIAccountServiceFactory()
    : ProfileKeyedServiceFactory("QorAIAccountService") {
  CHECK(features::IsQorAIAccountEnabled());
}

QorAIAccountServiceFactory::~QorAIAccountServiceFactory() = default;

bool QorAIAccountServiceFactory::ServiceIsCreatedWithBrowserContext() const {
  return true;
}

bool QorAIAccountServiceFactory::ServiceIsNULLWhileTesting() const {
  return true;
}

std::unique_ptr<KeyedService>
QorAIAccountServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  CHECK(context);
  return std::make_unique<QorAIAccountService>(
      Profile::FromBrowserContext(context)->GetPrefs(),
      context->GetDefaultStoragePartition()
          ->GetURLLoaderFactoryForBrowserProcess());
}

}  // namespace qorai_account
