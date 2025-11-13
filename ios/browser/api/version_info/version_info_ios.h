/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_VERSION_INFO_VERSION_INFO_IOS_H_
#define QORAI_IOS_BROWSER_API_VERSION_INFO_VERSION_INFO_IOS_H_

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSInteger QoraiCoreVersionInfoChannel
    NS_TYPED_ENUM NS_SWIFT_NAME(QoraiCoreVersionInfo.Channel);

OBJC_EXPORT QoraiCoreVersionInfoChannel const QoraiCoreVersionInfoChannelStable;
OBJC_EXPORT QoraiCoreVersionInfoChannel const QoraiCoreVersionInfoChannelBeta;
OBJC_EXPORT QoraiCoreVersionInfoChannel const
    QoraiCoreVersionInfoChannelDevelopment;
OBJC_EXPORT QoraiCoreVersionInfoChannel const
    QoraiCoreVersionInfoChannelNightly;
OBJC_EXPORT QoraiCoreVersionInfoChannel const
    QoraiCoreVersionInfoChannelUnknown;

OBJC_EXPORT
@interface QoraiCoreVersionInfo : NSObject
@property(class, readonly) NSString* qoraiCoreVersion;
@property(class, readonly) NSString* chromiumVersion;
@property(class, readonly) NSString* channelString;
@property(class, readonly) QoraiCoreVersionInfoChannel channel;

- (instancetype)init NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_VERSION_INFO_VERSION_INFO_IOS_H_
