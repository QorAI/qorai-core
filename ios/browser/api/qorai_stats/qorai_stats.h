/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_QORAI_STATS_QORAI_STATS_H_
#define QORAI_IOS_BROWSER_API_QORAI_STATS_QORAI_STATS_H_

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

OBJC_EXPORT NSString* const kQoraiStatsAPIKey;
/// The endpoint we want to submit webcompat reports to
OBJC_EXPORT NSString* const kWebcompatReportEndpoint;

OBJC_EXPORT
@interface QoraiStats : NSObject
@property(readonly) BOOL isStatsReportingManaged;
@property(nonatomic, getter=isStatsReportingEnabled)
    BOOL statsReportingEnabled NS_SWIFT_NAME(isStatsReportingEnabled);
/// Any additional wallet parameters to send with the DAU ping
@property(readonly) NSDictionary<NSString*, NSString*>* walletParams;
@property(readonly, getter=isNotificationAdsEnabled)
    BOOL notificationAdsEnabled;
/// Should be called when the stats ping has been sent
- (void)notifyStatsPingSent;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_QORAI_STATS_QORAI_STATS_H_
