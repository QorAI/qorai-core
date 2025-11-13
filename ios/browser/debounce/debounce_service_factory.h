// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_DEBOUNCE_DEBOUNCE_SERVICE_FACTORY_H_
#define QORAI_IOS_BROWSER_DEBOUNCE_DEBOUNCE_SERVICE_FACTORY_H_

#import <Foundation/Foundation.h>

#include "keyed_service_factory_wrapper.h"  // NOLINT

@protocol DebounceServiceBridge;

OBJC_EXPORT
@interface DebounceServiceFactory
    : KeyedServiceFactoryWrapper <id <DebounceServiceBridge>>
@end

#endif  // QORAI_IOS_BROWSER_DEBOUNCE_DEBOUNCE_SERVICE_FACTORY_H_
