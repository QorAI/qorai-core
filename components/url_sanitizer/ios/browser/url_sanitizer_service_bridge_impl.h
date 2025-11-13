// Copyright (c) 2025 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_URL_SANITIZER_IOS_BROWSER_URL_SANITIZER_SERVICE_BRIDGE_IMPL_H_
#define QORAI_COMPONENTS_URL_SANITIZER_IOS_BROWSER_URL_SANITIZER_SERVICE_BRIDGE_IMPL_H_

#import <Foundation/Foundation.h>

#include "base/memory/raw_ptr.h"
#include "qorai/components/url_sanitizer/ios/browser/url_sanitizer_service_bridge.h"

namespace qorai {
class URLSanitizerService;
}

NS_ASSUME_NONNULL_BEGIN

@interface URLSanitizerServiceBridgeImpl : NSObject <URLSanitizerServiceBridge>
@property(readonly) raw_ptr<qorai::URLSanitizerService> urlSanitizerService;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithURLSanitizerService:
    (raw_ptr<qorai::URLSanitizerService>)urlSanitizerService;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_COMPONENTS_URL_SANITIZER_IOS_BROWSER_URL_SANITIZER_SERVICE_BRIDGE_IMPL_H_
