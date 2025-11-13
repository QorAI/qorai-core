/* Copyright (c) 2024 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_WEBCOMPAT_REPORTER_WEBCOMPAT_REPORTER_SERVICE_FACTORY_WRAPPER_H_
#define QORAI_IOS_BROWSER_API_WEBCOMPAT_REPORTER_WEBCOMPAT_REPORTER_SERVICE_FACTORY_WRAPPER_H_

#import <Foundation/Foundation.h>

#include "keyed_service_factory_wrapper.h"  // NOLINT

@protocol WebcompatReporterWebcompatReporterHandler;

OBJC_EXPORT
NS_SWIFT_NAME(WebcompatReporter.ServiceFactory)
@interface WebcompatReporterServiceFactory
    : KeyedServiceFactoryWrapper <
          id <WebcompatReporterWebcompatReporterHandler>>
@end

#endif  // QORAI_IOS_BROWSER_API_WEBCOMPAT_REPORTER_WEBCOMPAT_REPORTER_SERVICE_FACTORY_WRAPPER_H_
