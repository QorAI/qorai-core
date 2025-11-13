/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_QORAI_ACCOUNT_QORAI_ACCOUNT_SERVICE_FACTORY_IOS_H_
#define QORAI_IOS_BROWSER_QORAI_ACCOUNT_QORAI_ACCOUNT_SERVICE_FACTORY_IOS_H_

#include <memory>

#include "base/no_destructor.h"
#include "ios/chrome/browser/shared/model/profile/profile_keyed_service_factory_ios.h"

class KeyedService;

namespace web {
class BrowserState;
}

namespace qorai_account {

class QoraiAccountService;

class QoraiAccountServiceFactoryIOS : public ProfileKeyedServiceFactoryIOS {
 public:
  QoraiAccountServiceFactoryIOS(const QoraiAccountServiceFactoryIOS&) = delete;
  QoraiAccountServiceFactoryIOS& operator=(
      const QoraiAccountServiceFactoryIOS&) = delete;

  static QoraiAccountServiceFactoryIOS* GetInstance();
  static QoraiAccountService* GetFor(web::BrowserState* state);

 private:
  friend base::NoDestructor<QoraiAccountServiceFactoryIOS>;

  QoraiAccountServiceFactoryIOS();
  ~QoraiAccountServiceFactoryIOS() override;

  // BrowserStateKeyedServiceFactory:
  std::unique_ptr<KeyedService> BuildServiceInstanceFor(
      ProfileIOS* profile) const override;
};

}  // namespace qorai_account

#endif  // QORAI_IOS_BROWSER_QORAI_ACCOUNT_QORAI_ACCOUNT_SERVICE_FACTORY_IOS_H_
