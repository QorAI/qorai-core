/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/ios/browser/qorai_account/qorai_account_service_factory_ios.h"

#include "qorai/components/qorai_account/qorai_account_service.h"
#include "qorai/components/qorai_account/features.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"
#include "ios/web/public/browser_state.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"

namespace qorai_account {

// static
QoraiAccountServiceFactoryIOS* QoraiAccountServiceFactoryIOS::GetInstance() {
  static base::NoDestructor<QoraiAccountServiceFactoryIOS> instance;
  return instance.get();
}

// static
QoraiAccountService* QoraiAccountServiceFactoryIOS::GetFor(
    web::BrowserState* state) {
  CHECK(state);
  return static_cast<QoraiAccountService*>(
      GetInstance()->GetServiceForContext(state, true));
}

QoraiAccountServiceFactoryIOS::QoraiAccountServiceFactoryIOS()
    : ProfileKeyedServiceFactoryIOS("QoraiAccountService",
                                    ServiceCreation::kCreateWithProfile,
                                    TestingCreation::kNoServiceForTests) {
  CHECK(features::IsQoraiAccountEnabled());
}

QoraiAccountServiceFactoryIOS::~QoraiAccountServiceFactoryIOS() = default;

std::unique_ptr<KeyedService>
QoraiAccountServiceFactoryIOS::BuildServiceInstanceFor(
    ProfileIOS* profile) const {
  CHECK(profile);
  return std::make_unique<QoraiAccountService>(
      profile->GetPrefs(), profile->GetSharedURLLoaderFactory());
}

}  // namespace qorai_account
