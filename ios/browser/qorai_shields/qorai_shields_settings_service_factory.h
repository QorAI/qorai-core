// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_QORAI_SHIELDS_QORAI_SHIELDS_SETTINGS_SERVICE_FACTORY_H_
#define QORAI_IOS_BROWSER_QORAI_SHIELDS_QORAI_SHIELDS_SETTINGS_SERVICE_FACTORY_H_

#include <memory>

#include "base/no_destructor.h"
#include "components/keyed_service/core/keyed_service.h"
#include "ios/chrome/browser/shared/model/profile/profile_keyed_service_factory_ios.h"

class ProfileIOS;

namespace base {

template <typename T>
class NoDestructor;
}  // namespace base

namespace qorai_shields {

class QoraiShieldsSettingsService;

class QoraiShieldsSettingsServiceFactory
    : public ProfileKeyedServiceFactoryIOS {
 public:
  static QoraiShieldsSettingsService* GetForProfile(ProfileIOS* profile);
  static QoraiShieldsSettingsServiceFactory* GetInstance();

  QoraiShieldsSettingsServiceFactory(
      const QoraiShieldsSettingsServiceFactory&) = delete;
  QoraiShieldsSettingsServiceFactory& operator=(
      const QoraiShieldsSettingsServiceFactory&) = delete;

 private:
  friend class base::NoDestructor<QoraiShieldsSettingsServiceFactory>;

  QoraiShieldsSettingsServiceFactory();
  ~QoraiShieldsSettingsServiceFactory() override;

  // ProfileKeyedServiceFactoryIOS implementation.
  std::unique_ptr<KeyedService> BuildServiceInstanceFor(
      ProfileIOS* context) const override;
};
}  // namespace qorai_shields

#endif  // QORAI_IOS_BROWSER_QORAI_SHIELDS_QORAI_SHIELDS_SETTINGS_SERVICE_FACTORY_H_
