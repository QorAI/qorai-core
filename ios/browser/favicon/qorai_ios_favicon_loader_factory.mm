/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#import "qorai/ios/browser/favicon/qorai_ios_favicon_loader_factory.h"

#include "base/no_destructor.h"
#import "qorai/ios/browser/favicon/qorai_ios_favicon_loader.h"
#include "components/keyed_service/core/service_access_type.h"
#include "components/keyed_service/ios/browser_state_keyed_service_factory.h"
#include "ios/chrome/browser/favicon/model/favicon_service_factory.h"
#import "ios/chrome/browser/favicon/model/ios_chrome_large_icon_service_factory.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"

#if !defined(__has_feature) || !__has_feature(objc_arc)
#error "This file requires ARC support."
#endif

namespace {

std::unique_ptr<KeyedService> BuildFaviconLoader(ProfileIOS* profile) {
  return std::make_unique<qorai_favicon::QoraiFaviconLoader>(
      ios::FaviconServiceFactory::GetForProfile(
          profile, ServiceAccessType::EXPLICIT_ACCESS));
}

}  // namespace

namespace qorai_favicon {
QoraiFaviconLoader* QoraiIOSFaviconLoaderFactory::GetForProfile(
    ProfileIOS* profile) {
  return GetInstance()->GetServiceForProfileAs<QoraiFaviconLoader>(profile,
                                                                   true);
}

QoraiFaviconLoader* QoraiIOSFaviconLoaderFactory::GetForProfileIfExists(
    ProfileIOS* profile) {
  return GetInstance()->GetServiceForProfileAs<QoraiFaviconLoader>(profile,
                                                                   false);
}

QoraiIOSFaviconLoaderFactory* QoraiIOSFaviconLoaderFactory::GetInstance() {
  static base::NoDestructor<QoraiIOSFaviconLoaderFactory> instance;
  return instance.get();
}

// static
ProfileKeyedServiceFactoryIOS::TestingFactory
QoraiIOSFaviconLoaderFactory::GetDefaultFactory() {
  return base::BindRepeating(&BuildFaviconLoader);
}

QoraiIOSFaviconLoaderFactory::QoraiIOSFaviconLoaderFactory()
    : ProfileKeyedServiceFactoryIOS("QoraiFaviconLoader",
                                    ProfileSelection::kRedirectedInIncognito,
                                    ServiceCreation::kCreateLazily,
                                    TestingCreation::kNoServiceForTests) {
  DependsOn(ios::FaviconServiceFactory::GetInstance());
  DependsOn(IOSChromeLargeIconServiceFactory::GetInstance());
}

QoraiIOSFaviconLoaderFactory::~QoraiIOSFaviconLoaderFactory() {}

std::unique_ptr<KeyedService>
QoraiIOSFaviconLoaderFactory::BuildServiceInstanceFor(
    ProfileIOS* profile) const {
  return BuildFaviconLoader(profile);
}
}  // namespace qorai_favicon
