// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_QORAI_SHIELDS_QORAI_SHIELDS_SETTINGS_SERVICE_FACTORY_H_
#define QORAI_BROWSER_QORAI_SHIELDS_QORAI_SHIELDS_SETTINGS_SERVICE_FACTORY_H_

#include <memory>

#include "base/no_destructor.h"
#include "chrome/browser/profiles/profile_keyed_service_factory.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/browser_context.h"

class Profile;

namespace qorai_shields {
class QoraiShieldsSettingsService;
}

class QoraiShieldsSettingsServiceFactory : public ProfileKeyedServiceFactory {
 public:
  static QoraiShieldsSettingsServiceFactory* GetInstance();
  static qorai_shields::QoraiShieldsSettingsService* GetForProfile(
      Profile* profile);

 private:
  friend base::NoDestructor<QoraiShieldsSettingsServiceFactory>;

  QoraiShieldsSettingsServiceFactory();
  ~QoraiShieldsSettingsServiceFactory() override;

  // ProfileKeyedServiceFactory overrides:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
};

#endif  // QORAI_BROWSER_QORAI_SHIELDS_QORAI_SHIELDS_SETTINGS_SERVICE_FACTORY_H_
