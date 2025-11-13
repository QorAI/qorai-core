// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/ios/browser/qorai_shields/qorai_shields_settings_service_factory.h"

#include "base/no_destructor.h"
#include "qorai/components/qorai_shields/core/browser/qorai_shields_settings_service.h"
#include "components/user_prefs/user_prefs.h"
#include "ios/chrome/browser/content_settings/model/host_content_settings_map_factory.h"
#include "ios/chrome/browser/shared/model/application_context/application_context.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"

namespace qorai_shields {

// static
QoraiShieldsSettingsService* QoraiShieldsSettingsServiceFactory::GetForProfile(
    ProfileIOS* profile) {
  return GetInstance()->GetServiceForProfileAs<QoraiShieldsSettingsService>(
      profile, true);
}

// static
QoraiShieldsSettingsServiceFactory*
QoraiShieldsSettingsServiceFactory::GetInstance() {
  static base::NoDestructor<QoraiShieldsSettingsServiceFactory> instance;
  return instance.get();
}

QoraiShieldsSettingsServiceFactory::QoraiShieldsSettingsServiceFactory()
    : ProfileKeyedServiceFactoryIOS("QoraiShieldsSettingsService",
                                    ProfileSelection::kOwnInstanceInIncognito,
                                    ServiceCreation::kCreateLazily,
                                    TestingCreation::kCreateService) {
  DependsOn(ios::HostContentSettingsMapFactory::GetInstance());
}

QoraiShieldsSettingsServiceFactory::~QoraiShieldsSettingsServiceFactory() {}

std::unique_ptr<KeyedService>
QoraiShieldsSettingsServiceFactory::BuildServiceInstanceFor(
    ProfileIOS* profile) const {
  auto* map = ios::HostContentSettingsMapFactory::GetForProfile(profile);
  CHECK(map);
  auto* local_state = GetApplicationContext()->GetLocalState();

  return std::make_unique<QoraiShieldsSettingsService>(*map, local_state,
                                                       profile->GetPrefs());
}

}  // namespace qorai_shields
