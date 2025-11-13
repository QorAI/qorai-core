// Copyright (c) 2024 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/qorai_shields/qorai_farbling_service_factory.h"

#include "base/no_destructor.h"
#include "qorai/components/qorai_shields/content/browser/qorai_farbling_service.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "content/public/browser/browser_context.h"

namespace qorai {

// static
QorAIFarblingServiceFactory* QorAIFarblingServiceFactory::GetInstance() {
  static base::NoDestructor<QorAIFarblingServiceFactory> instance;
  return instance.get();
}

// static
QorAIFarblingService* QorAIFarblingServiceFactory::GetForProfile(
    Profile* profile) {
  return static_cast<QorAIFarblingService*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));
}

QorAIFarblingServiceFactory::QorAIFarblingServiceFactory()
    : ProfileKeyedServiceFactory(
          "QorAIFarblingService",
          ProfileSelections::Builder()
              .WithRegular(ProfileSelection::kOwnInstance)
              .WithGuest(ProfileSelection::kOwnInstance)
              .WithSystem(ProfileSelection::kNone)
              .Build()) {
  DependsOn(HostContentSettingsMapFactory::GetInstance());
}

QorAIFarblingServiceFactory::~QorAIFarblingServiceFactory() = default;

std::unique_ptr<KeyedService>
QorAIFarblingServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  return std::make_unique<QorAIFarblingService>(
      HostContentSettingsMapFactory::GetForProfile(context));
}

}  // namespace qorai
