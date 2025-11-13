/* Copyright (c) 2019 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_REWARDS_REWARDS_SERVICE_FACTORY_H_
#define QORAI_BROWSER_QORAI_REWARDS_REWARDS_SERVICE_FACTORY_H_

#include <memory>

#include "qorai/components/qorai_rewards/content/rewards_service.h"
#include "chrome/browser/profiles/profile_manager_observer.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

class Profile;

namespace base {
template <typename T>
class NoDestructor;
}  // namespace base

namespace qorai_rewards {
class RewardsService;

// Singleton that owns all RewardsService and associates them with Profiles.
class RewardsServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  RewardsServiceFactory(const RewardsServiceFactory&) = delete;
  RewardsServiceFactory& operator=(const RewardsServiceFactory&) = delete;

  static qorai_rewards::RewardsService* GetForProfile(Profile* profile);

  static RewardsServiceFactory* GetInstance();

  static void SetServiceForTesting(RewardsService* service);

 private:
  friend base::NoDestructor<RewardsServiceFactory>;

  RewardsServiceFactory();
  ~RewardsServiceFactory() override = default;

  // BrowserContextKeyedServiceFactory:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
  bool ServiceIsNULLWhileTesting() const override;
};

}  // namespace qorai_rewards

#endif  // QORAI_BROWSER_QORAI_REWARDS_REWARDS_SERVICE_FACTORY_H_
