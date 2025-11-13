/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/ios/browser/qorai_wallet/qorai_wallet_ipfs_service_factory.h"

#include "qorai/components/qorai_wallet/browser/qorai_wallet_ipfs_service.h"
#include "qorai/components/qorai_wallet/browser/pref_names.h"
#include "components/keyed_service/core/keyed_service.h"
#include "ios/chrome/browser/shared/model/application_context/application_context.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"
#include "ios/web/public/browser_state.h"

namespace qorai_wallet {

// static
mojo::PendingRemote<mojom::IpfsService>
QoraiWalletIpfsServiceFactory::GetForProfile(ProfileIOS* profile) {
  return GetInstance()
      ->GetServiceForProfileAs<QoraiWalletIpfsService>(profile, true)
      ->MakeRemote();
}

// static
QoraiWalletIpfsService* QoraiWalletIpfsServiceFactory::GetServiceForState(
    ProfileIOS* profile) {
  return GetInstance()->GetServiceForProfileAs<QoraiWalletIpfsService>(profile,
                                                                       true);
}

// static
QoraiWalletIpfsServiceFactory* QoraiWalletIpfsServiceFactory::GetInstance() {
  static base::NoDestructor<QoraiWalletIpfsServiceFactory> instance;
  return instance.get();
}

QoraiWalletIpfsServiceFactory::QoraiWalletIpfsServiceFactory()
    : ProfileKeyedServiceFactoryIOS("QoraiWalletIpfsService",
                                    ProfileSelection::kRedirectedInIncognito,
                                    ServiceCreation::kCreateLazily,
                                    TestingCreation::kNoServiceForTests) {}

QoraiWalletIpfsServiceFactory::~QoraiWalletIpfsServiceFactory() = default;

std::unique_ptr<KeyedService>
QoraiWalletIpfsServiceFactory::BuildServiceInstanceFor(
    ProfileIOS* profile) const {
  std::unique_ptr<QoraiWalletIpfsService> ipfs_service(
      new QoraiWalletIpfsService(profile->GetPrefs()));
  return ipfs_service;
}

}  // namespace qorai_wallet
