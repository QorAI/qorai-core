/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_QORAI_REWARDS_REWARDS_NOTIFICATION_H_
#define QORAI_IOS_BROWSER_API_QORAI_REWARDS_REWARDS_NOTIFICATION_H_

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, RewardsNotificationKind) {
  RewardsNotificationKindInvalid,
  RewardsNotificationKindAutoContribute,
  RewardsNotificationKindFailedContribution,
  RewardsNotificationKindInsufficientFunds,
  RewardsNotificationKindTipsProcessed,
  RewardsNotificationKindAdsLaunch,              // Unused
  RewardsNotificationKindVerifiedPublisher,      // Unused
  RewardsNotificationKindPendingNotEnoughFunds,  // Unused
  RewardsNotificationKindGeneral
} NS_SWIFT_NAME(RewardsNotification.Kind);

OBJC_EXPORT
@interface RewardsNotification : NSObject <NSSecureCoding>

@property(nonatomic, copy) NSString* id;
@property(nonatomic) NSTimeInterval dateAdded;
@property(nonatomic) RewardsNotificationKind kind;
@property(nonatomic, copy) NSDictionary* userInfo;
@property(nonatomic) BOOL displayed;

- (instancetype)initWithID:(NSString*)notificationID
                 dateAdded:(NSTimeInterval)dateAdded
                      kind:(RewardsNotificationKind)kind
                  userInfo:(nullable NSDictionary*)userInfo;

@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_QORAI_REWARDS_REWARDS_NOTIFICATION_H_
