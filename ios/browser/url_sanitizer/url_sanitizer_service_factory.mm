/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/ios/browser/url_sanitizer/url_sanitizer_service_factory.h"

#include "base/no_destructor.h"
#include "qorai/components/url_sanitizer/core/browser/url_sanitizer_component_installer.h"
#include "qorai/components/url_sanitizer/core/browser/url_sanitizer_service.h"
#include "qorai/components/url_sanitizer/ios/browser/url_sanitizer_service_bridge_impl.h"
#include "qorai/ios/browser/application_context/qorai_application_context_impl.h"
#include "qorai/ios/browser/keyed_service/keyed_service_factory_wrapper+private.h"
#include "qorai/ios/browser/url_sanitizer/url_sanitizer_service_factory+private.h"
#include "components/keyed_service/core/keyed_service.h"
#include "ios/chrome/browser/shared/model/application_context/application_context.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"
#include "ios/web/public/browser_state.h"

#if !defined(__has_feature) || !__has_feature(objc_arc)
#error "This file requires ARC support."
#endif

@implementation URLSanitizerServiceFactory
+ (nullable id)serviceForProfile:(ProfileIOS*)profile {
  // Create and start the local data file service and component installer
  qorai::URLSanitizerService* urlSanitizer =
      qorai::URLSanitizerServiceFactory::GetServiceForState(profile);
  return [[URLSanitizerServiceBridgeImpl alloc]
      initWithURLSanitizerService:urlSanitizer];
}
@end

namespace qorai {

// static
qorai::URLSanitizerService* URLSanitizerServiceFactory::GetServiceForState(
    ProfileIOS* profile) {
  return GetInstance()->GetServiceForProfileAs<qorai::URLSanitizerService>(
      profile, true);
}

// static
URLSanitizerServiceFactory* URLSanitizerServiceFactory::GetInstance() {
  static base::NoDestructor<URLSanitizerServiceFactory> instance;
  return instance.get();
}

URLSanitizerServiceFactory::URLSanitizerServiceFactory()
    : ProfileKeyedServiceFactoryIOS("URLSanitizerService",
                                    ProfileSelection::kRedirectedInIncognito,
                                    ServiceCreation::kCreateWithProfile,
                                    TestingCreation::kNoServiceForTests) {}

URLSanitizerServiceFactory::~URLSanitizerServiceFactory() = default;

std::unique_ptr<KeyedService>
URLSanitizerServiceFactory::BuildServiceInstanceFor(ProfileIOS* profile) const {
  std::unique_ptr<qorai::URLSanitizerService> service =
      std::make_unique<qorai::URLSanitizerService>();
  QoraiApplicationContextImpl* qoraiContext =
      static_cast<QoraiApplicationContextImpl*>(GetApplicationContext());
  qoraiContext->url_sanitizer_component_installer()->AddObserver(service.get());
  return service;
}

}  // namespace qorai
