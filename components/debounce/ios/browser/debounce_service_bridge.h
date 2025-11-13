// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_COMPONENTS_DEBOUNCE_IOS_BROWSER_DEBOUNCE_SERVICE_BRIDGE_H_
#define QORAI_COMPONENTS_DEBOUNCE_IOS_BROWSER_DEBOUNCE_SERVICE_BRIDGE_H_

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// A bridge used to use methods found on debounce::DebounceService
NS_SWIFT_NAME(DebounceService)
@protocol DebounceServiceBridge
/// Whether or not debounce is enabled
@property(nonatomic, getter=isEnabled) BOOL enabled NS_SWIFT_NAME(isEnabled);
/// Returns a debounced URL or nil if no debounce rule is applied to the URL
- (nullable NSURL*)debounceURL:(NSURL*)url NS_SWIFT_NAME(debounce(url:));
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_COMPONENTS_DEBOUNCE_IOS_BROWSER_DEBOUNCE_SERVICE_BRIDGE_H_
