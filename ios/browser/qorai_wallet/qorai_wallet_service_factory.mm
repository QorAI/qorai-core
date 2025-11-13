/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/ios/browser/qorai_wallet/qorai_wallet_service_factory.h"

#include <memory>

#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service_delegate.h"
#include "components/keyed_service/core/keyed_service.h"
#include "ios/chrome/browser/shared/model/application_context/application_context.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"
#include "ios/web/public/browser_state.h"
#include "services/network/public/cpp/shared_url_loader_factory.h"

namespace qorai_wallet {

class QoraiWalletServiceDelegateIos : public QoraiWalletServiceDelegate {
 public:
  explicit QoraiWalletServiceDelegateIos(ProfileIOS* profile) {
    wallet_base_directory_ = profile->GetStatePath();
    is_private_window_ = profile->IsOffTheRecord();
  }

  base::FilePath GetWalletBaseDirectory() override {
    return wallet_base_directory_;
  }
  bool IsPrivateWindow() override { return is_private_window_; }

 protected:
  base::FilePath wallet_base_directory_;
  bool is_private_window_ = false;
};

// static
QoraiWalletService* QoraiWalletServiceFactory::GetServiceForState(
    ProfileIOS* profile) {
  return GetInstance()->GetServiceForProfileAs<QoraiWalletService>(profile,
                                                                   true);
}

// static
QoraiWalletServiceFactory* QoraiWalletServiceFactory::GetInstance() {
  static base::NoDestructor<QoraiWalletServiceFactory> instance;
  return instance.get();
}

QoraiWalletServiceFactory::QoraiWalletServiceFactory()
    : ProfileKeyedServiceFactoryIOS("QoraiWalletService",
                                    ProfileSelection::kRedirectedInIncognito,
                                    ServiceCreation::kCreateLazily,
                                    TestingCreation::kNoServiceForTests) {}

QoraiWalletServiceFactory::~QoraiWalletServiceFactory() = default;

std::unique_ptr<KeyedService>
QoraiWalletServiceFactory::BuildServiceInstanceFor(ProfileIOS* profile) const {
  std::unique_ptr<QoraiWalletService> service(new QoraiWalletService(
      profile->GetSharedURLLoaderFactory(),
      std::make_unique<QoraiWalletServiceDelegateIos>(profile),
      profile->GetPrefs(), GetApplicationContext()->GetLocalState()));
  return service;
}

}  // namespace qorai_wallet
