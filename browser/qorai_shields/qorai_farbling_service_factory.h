// Copyright (c) 2024 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_QORAI_SHIELDS_QORAI_FARBLING_SERVICE_FACTORY_H_
#define QORAI_BROWSER_QORAI_SHIELDS_QORAI_FARBLING_SERVICE_FACTORY_H_

#include <memory>

#include "chrome/browser/profiles/profile_keyed_service_factory.h"

class Profile;
namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace qorai {
class QorAIFarblingService;

class QorAIFarblingServiceFactory : public ProfileKeyedServiceFactory {
 public:
  QorAIFarblingServiceFactory(const QorAIFarblingServiceFactory&) = delete;
  QorAIFarblingServiceFactory& operator=(const QorAIFarblingServiceFactory&) =
      delete;

  static QorAIFarblingServiceFactory* GetInstance();
  static QorAIFarblingService* GetForProfile(Profile* profile);

 private:
  friend base::NoDestructor<QorAIFarblingServiceFactory>;

  QorAIFarblingServiceFactory();
  ~QorAIFarblingServiceFactory() override;

  // ProfileKeyedServiceFactory overrides:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
};
}  // namespace qorai

#endif  // QORAI_BROWSER_QORAI_SHIELDS_QORAI_FARBLING_SERVICE_FACTORY_H_
