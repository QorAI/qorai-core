/* Copyright (c) 2025 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_QORAI_ACCOUNT_QORAI_ACCOUNT_AUTHENTICATION_BRIDGE_H_
#define QORAI_IOS_BROWSER_QORAI_ACCOUNT_QORAI_ACCOUNT_AUTHENTICATION_BRIDGE_H_

#import <Foundation/Foundation.h>

NS_SWIFT_NAME(QoraiAccountAuthentication)
@protocol QoraiAccountAuthenticationBridge

- (void)resendConfirmationEmail;
- (void)cancelRegistration;
- (void)logOut;

@end

#endif  // QORAI_IOS_BROWSER_QORAI_ACCOUNT_QORAI_ACCOUNT_AUTHENTICATION_BRIDGE_H_
