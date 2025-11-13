/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_WEB_DISCOVERY_WEB_DISCOVERY_SERVICE_FACTORY_H_
#define QORAI_BROWSER_WEB_DISCOVERY_WEB_DISCOVERY_SERVICE_FACTORY_H_

#include <memory>

#include "base/no_destructor.h"
#include "chrome/browser/profiles/profile_keyed_service_factory.h"

namespace web_discovery {

class WebDiscoveryService;

class WebDiscoveryServiceFactory : public ProfileKeyedServiceFactory {
 public:
  static WebDiscoveryServiceFactory* GetInstance();
  static WebDiscoveryService* GetForBrowserContext(
      content::BrowserContext* context);

 private:
  friend base::NoDestructor<WebDiscoveryServiceFactory>;

  WebDiscoveryServiceFactory();
  ~WebDiscoveryServiceFactory() override;

  WebDiscoveryServiceFactory(const WebDiscoveryServiceFactory&) = delete;
  WebDiscoveryServiceFactory& operator=(const WebDiscoveryServiceFactory&) =
      delete;

  static ProfileSelections CreateProfileSelections();

  // ProfileKeyedServiceFactory overrides:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
  bool ServiceIsCreatedWithBrowserContext() const override;
};

}  // namespace web_discovery

#endif  // QORAI_BROWSER_WEB_DISCOVERY_WEB_DISCOVERY_SERVICE_FACTORY_H_
