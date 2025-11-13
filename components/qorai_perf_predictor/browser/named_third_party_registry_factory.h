/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_COMPONENTS_QORAI_PERF_PREDICTOR_BROWSER_NAMED_THIRD_PARTY_REGISTRY_FACTORY_H_
#define QORAI_COMPONENTS_QORAI_PERF_PREDICTOR_BROWSER_NAMED_THIRD_PARTY_REGISTRY_FACTORY_H_

#include <memory>

#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#include "components/keyed_service/core/keyed_service.h"

class Profile;

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace qorai_perf_predictor {

class NamedThirdPartyRegistry;

class NamedThirdPartyRegistryFactory
    : public BrowserContextKeyedServiceFactory {
 public:
  static NamedThirdPartyRegistryFactory* GetInstance();
  static NamedThirdPartyRegistry* GetForBrowserContext(
      content::BrowserContext* context);

 private:
  friend base::NoDestructor<NamedThirdPartyRegistryFactory>;
  NamedThirdPartyRegistryFactory();
  ~NamedThirdPartyRegistryFactory() override;

  NamedThirdPartyRegistryFactory(const NamedThirdPartyRegistryFactory&) =
      delete;
  NamedThirdPartyRegistryFactory& operator=(
      const NamedThirdPartyRegistryFactory&) = delete;

  // BrowserContextKeyedServiceFactory overrides:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
  bool ServiceIsCreatedWithBrowserContext() const override;
};

}  // namespace qorai_perf_predictor

#endif  // QORAI_COMPONENTS_QORAI_PERF_PREDICTOR_BROWSER_NAMED_THIRD_PARTY_REGISTRY_FACTORY_H_
