/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_QORAI_ACCOUNT_QORAI_ACCOUNT_AUTHENTICATION_BRIDGE_IMPL_H_
#define QORAI_IOS_BROWSER_QORAI_ACCOUNT_QORAI_ACCOUNT_AUTHENTICATION_BRIDGE_IMPL_H_

#import <Foundation/Foundation.h>

#include "qorai_account_authentication_bridge.h"

@protocol ProfileBridge;

NS_ASSUME_NONNULL_BEGIN

OBJC_EXPORT NSString* const QoraiAccountAuthenticationTokenPref;
OBJC_EXPORT NSString* const QoraiAccountVerificationTokenPref;

OBJC_EXPORT
@interface QoraiAccountAuthenticationBridgeImpl
    : NSObject <QoraiAccountAuthenticationBridge>
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithProfile:(id<ProfileBridge>)profile
    NS_DESIGNATED_INITIALIZER;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_QORAI_ACCOUNT_QORAI_ACCOUNT_AUTHENTICATION_BRIDGE_IMPL_H_
