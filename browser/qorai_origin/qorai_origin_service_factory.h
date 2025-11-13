/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_BROWSER_QORAI_ORIGIN_QORAI_ORIGIN_SERVICE_FACTORY_H_
#define QORAI_BROWSER_QORAI_ORIGIN_QORAI_ORIGIN_SERVICE_FACTORY_H_

#include "qorai/components/qorai_origin/qorai_origin_policy_info.h"
#include "chrome/browser/profiles/profile_keyed_service_factory.h"

namespace base {
template <typename T>
class NoDestructor;
}

class Profile;

namespace qorai_origin {

class QoraiOriginService;

// Factory for QoraiOriginService keyed service.
class QoraiOriginServiceFactory : public ProfileKeyedServiceFactory {
 public:
  static QoraiOriginService* GetForProfile(Profile* profile);
  static QoraiOriginServiceFactory* GetInstance();

  QoraiOriginServiceFactory(const QoraiOriginServiceFactory&) = delete;
  QoraiOriginServiceFactory& operator=(const QoraiOriginServiceFactory&) =
      delete;

  // Build browser-level policy definitions.
  // This is done in this layer because of all the dependencies needed
  // to gather this information.
  static QoraiOriginPolicyMap GetBrowserPolicyDefinitions();

  // Build profile-level policy definitions for a specific profile.
  static QoraiOriginPolicyMap GetProfilePolicyDefinitions();

  // Static QoraiOrigin-specific metadata for policy preferences.
  // This defines which preferences from kQoraiSimplePolicyMap should have
  // QoraiOrigin behavior and specifies their QoraiOrigin-specific configuration
  // (default values, scope, UI visibility). Used only during initialization
  // to populate QoraiOriginPrefInfo structs.
  struct QoraiOriginPrefMetadata {
    constexpr QoraiOriginPrefMetadata(bool origin_default_value,
                                      bool user_settable)
        : origin_default_value(origin_default_value),
          user_settable(user_settable) {}
    constexpr ~QoraiOriginPrefMetadata() = default;

    // Allow copy operations for MakeFixedFlatMap
    constexpr QoraiOriginPrefMetadata(const QoraiOriginPrefMetadata&) = default;
    constexpr QoraiOriginPrefMetadata& operator=(
        const QoraiOriginPrefMetadata&) = default;

    constexpr QoraiOriginPrefMetadata(QoraiOriginPrefMetadata&&) = default;
    constexpr QoraiOriginPrefMetadata& operator=(QoraiOriginPrefMetadata&&) =
        default;

    bool origin_default_value;
    bool user_settable;
  };

 private:
  friend base::NoDestructor<QoraiOriginServiceFactory>;

  QoraiOriginServiceFactory();
  ~QoraiOriginServiceFactory() override;

  // ProfileKeyedServiceFactory:
  std::unique_ptr<KeyedService> BuildServiceInstanceForBrowserContext(
      content::BrowserContext* context) const override;
  bool ServiceIsCreatedWithBrowserContext() const override;
};

}  // namespace qorai_origin

#endif  // QORAI_BROWSER_QORAI_ORIGIN_QORAI_ORIGIN_SERVICE_FACTORY_H_
