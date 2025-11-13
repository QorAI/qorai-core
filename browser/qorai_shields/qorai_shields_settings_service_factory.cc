// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/qorai_shields/qorai_shields_settings_service_factory.h"

#include "base/no_destructor.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_settings_service.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/content_settings/host_content_settings_map_factory.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_selections.h"
#include "content/public/browser/browser_context.h"

// static
QoraiShieldsSettingsServiceFactory*
QoraiShieldsSettingsServiceFactory::GetInstance() {
  static base::NoDestructor<QoraiShieldsSettingsServiceFactory> instance;
  return instance.get();
}

// static
qorai_shields::QoraiShieldsSettingsService*
QoraiShieldsSettingsServiceFactory::GetForProfile(Profile* profile) {
  return static_cast<qorai_shields::QoraiShieldsSettingsService*>(
      GetInstance()->GetServiceForBrowserContext(profile, true));
}

QoraiShieldsSettingsServiceFactory::QoraiShieldsSettingsServiceFactory()
    : ProfileKeyedServiceFactory(
          "QoraiShieldsSettingsService",
          ProfileSelections::Builder()
              // this should match HostContentSettingsMapFactory
              .WithRegular(ProfileSelection::kOwnInstance)
              .WithGuest(ProfileSelection::kOwnInstance)
              .Build()) {
  DependsOn(HostContentSettingsMapFactory::GetInstance());
}

QoraiShieldsSettingsServiceFactory::~QoraiShieldsSettingsServiceFactory() =
    default;

std::unique_ptr<KeyedService>
QoraiShieldsSettingsServiceFactory::BuildServiceInstanceForBrowserContext(
    content::BrowserContext* context) const {
  auto* profile = Profile::FromBrowserContext(context);
  auto* map = HostContentSettingsMapFactory::GetForProfile(profile);
  CHECK(map);
  return std::make_unique<qorai_shields::QoraiShieldsSettingsService>(
      *map, g_browser_process->local_state(), profile->GetPrefs());
}
