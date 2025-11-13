// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_IOS_BROWSER_API_QORAI_USER_AGENT_QORAI_USER_AGENT_EXCEPTIONS_IOS_H_
#define QORAI_IOS_BROWSER_API_QORAI_USER_AGENT_QORAI_USER_AGENT_EXCEPTIONS_IOS_H_

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

OBJC_EXPORT
@interface QoraiUserAgentExceptionsIOS : NSObject

- (instancetype)init NS_UNAVAILABLE;
/// This returns if a url can show Qorai in User Agent
- (bool)canShowQorai:(NSURL*)url;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_QORAI_USER_AGENT_QORAI_USER_AGENT_EXCEPTIONS_IOS_H_
