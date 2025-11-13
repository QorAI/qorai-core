/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_FAVICON_QORAI_IOS_FAVICON_LOADER_FACTORY_H_
#define QORAI_IOS_BROWSER_FAVICON_QORAI_IOS_FAVICON_LOADER_FACTORY_H_

#include <memory>

#include "base/no_destructor.h"
#include "ios/chrome/browser/shared/model/profile/profile_keyed_service_factory_ios.h"

class ProfileIOS;

namespace qorai_favicon {
class QoraiFaviconLoader;

// Singleton that owns all FaviconLoaders and associates them with
// ProfileIOS.
class QoraiIOSFaviconLoaderFactory : public ProfileKeyedServiceFactoryIOS {
 public:
  static QoraiFaviconLoader* GetForProfile(ProfileIOS* profile);
  static QoraiFaviconLoader* GetForProfileIfExists(ProfileIOS* profile);
  static QoraiIOSFaviconLoaderFactory* GetInstance();
  static TestingFactory GetDefaultFactory();

  QoraiIOSFaviconLoaderFactory(const QoraiIOSFaviconLoaderFactory&) = delete;
  QoraiIOSFaviconLoaderFactory& operator=(const QoraiIOSFaviconLoaderFactory&) =
      delete;

 private:
  friend class base::NoDestructor<QoraiIOSFaviconLoaderFactory>;

  QoraiIOSFaviconLoaderFactory();
  ~QoraiIOSFaviconLoaderFactory() override;

  // ProfileKeyedServiceFactoryIOS implementation.
  std::unique_ptr<KeyedService> BuildServiceInstanceFor(
      ProfileIOS* profile) const override;
};
}  // namespace qorai_favicon

#endif  // QORAI_IOS_BROWSER_FAVICON_QORAI_IOS_FAVICON_LOADER_FACTORY_H_
