// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ntp_background/qorai_ntp_custom_background_service_factory.h"

#include <memory>

#include "base/no_destructor.h"
#include "qorai/browser/ntp_background/qorai_ntp_custom_background_service_delegate.h"
#include "qorai/components/ntp_background_images/browser/qorai_ntp_custom_background_service.h"
#include "chrome/browser/profiles/profile.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"

// static
ntp_background_images::QoraiNTPCustomBackgroundService*
QoraiNTPCustomBackgroundServiceFactory::GetForContext(
    content::BrowserContext* context) {
  return static_cast<ntp_background_images::QoraiNTPCustomBackgroundService*>(
      GetInstance()->GetServiceForBrowserContext(context, true));
}

// static
QoraiNTPCustomBackgroundServiceFactory*
QoraiNTPCustomBackgroundServiceFactory::GetInstance() {
  static base::NoDestructor<QoraiNTPCustomBackgroundServiceFactory> instance;
  return instance.get();
}

QoraiNTPCustomBackgroundServiceFactory::QoraiNTPCustomBackgroundServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "QoraiNTPCustomBackgroundService",
          BrowserContextDependencyManager::GetInstance()) {}

QoraiNTPCustomBackgroundServiceFactory::
    ~QoraiNTPCustomBackgroundServiceFactory() = default;

std::unique_ptr<KeyedService>
QoraiNTPCustomBackgroundServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  // Custom NTP background is only used in normal profile.
  if (!Profile::FromBrowserContext(context)->IsRegularProfile()) {
    return nullptr;
  }

  return std::make_unique<
      ntp_background_images::QoraiNTPCustomBackgroundService>(
      std::make_unique<QoraiNTPCustomBackgroundServiceDelegate>(
          Profile::FromBrowserContext(context)));
}
