/* Copyright (c) 2023 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_QORAI_REWARDS_QORAI_REWARDS_API_H_
#define QORAI_IOS_BROWSER_API_QORAI_REWARDS_QORAI_REWARDS_API_H_

#import <Foundation/Foundation.h>

#import "rewards.mojom.objc.h"

@class RewardsObserver, RewardsNotification;

NS_ASSUME_NONNULL_BEGIN

typedef NSString* ExternalWalletType NS_SWIFT_NAME(ExternalWalletType)
    NS_STRING_ENUM;

static ExternalWalletType const ExternalWalletTypeUphold = @"uphold";
static ExternalWalletType const ExternalWalletTypeAnonymous = @"anonymous";
static ExternalWalletType const ExternalWalletTypeUnblindedTokens = @"blinded";

@protocol PrefServiceBridge;

/// The error domain for rewards related errors
OBJC_EXPORT NSString* const QoraiRewardsErrorDomain;

OBJC_EXPORT NSNotificationName const
    QoraiRewardsNotificationAdded NS_SWIFT_NAME(QoraiRewardsAPI.notificationAdded);

typedef NSString* QoraiGeneralRewardsNotificationID NS_STRING_ENUM;
OBJC_EXPORT QoraiGeneralRewardsNotificationID const
    QoraiGeneralRewardsNotificationIDWalletNowVerified;
OBJC_EXPORT QoraiGeneralRewardsNotificationID const
    QoraiGeneralRewardsNotificationIDWalletDisconnected;

OBJC_EXPORT NSString* const QoraiRewardsDisabledByPolicyPrefName;

OBJC_EXPORT
@interface QoraiRewardsAPI : NSObject

+ (BOOL)isSupported:(id<PrefServiceBridge>)prefService;

/// Create a rewards engine that will read and write its state to the given path
- (instancetype)initWithStateStoragePath:(NSString*)path;

- (instancetype)init NS_UNAVAILABLE;

#pragma mark - Initialization

/// Initialize the rewards service.
///
/// This must be called before other methods on this class are called
- (void)initializeRewardsService:(nullable void (^)())completion;

/// Whether or not the rewards service has been initialized already
@property(nonatomic, readonly, getter=isInitialized) BOOL initialized;

/// Whether or not the rewards service is currently initializing
@property(nonatomic, readonly, getter=isInitializing) BOOL initializing;

/// The result when initializing the rewards service. Should be
/// `QoraiRewardsResultOk` if `initialized` is `true`
///
/// If this is not `QoraiRewardsResultOk`, rewards is not usable for the
/// user
@property(nonatomic, readonly) QoraiRewardsResult initializationResult;

/// Whether or not data migration failed when initializing and the user should
/// be notified.
@property(nonatomic, readonly) BOOL dataMigrationFailed;

#pragma mark - Observers

/// Add an interface to the list of observers
///
/// Observers are stored weakly and do not necessarily need to be removed
- (void)addObserver:(RewardsObserver*)observer;

/// Removes an interface from the list of observers
- (void)removeObserver:(RewardsObserver*)observer;

#pragma mark - Wallet

/// Whether or not the wallet is currently in the process of being created
@property(nonatomic, readonly, getter=isInitializingWallet)
    BOOL initializingWallet;

/// Creates a cryptocurrency wallet
- (void)createWallet:(nullable void (^)(NSError* _Nullable error))completion;

/// Get the qorai wallet's payment ID and seed for ads confirmations
- (void)currentWalletInfo:
    (void (^)(QoraiRewardsRewardsWallet* _Nullable wallet))completion;

/// Get parameters served from the server
- (void)getRewardsParameters:
    (nullable void (^)(QoraiRewardsRewardsParameters* _Nullable))completion;

/// The parameters send from the server
@property(nonatomic, readonly, nullable)
    QoraiRewardsRewardsParameters* rewardsParameters;

/// Fetch details about the users wallet (if they have one) and assigns it to
/// `balance`
- (void)fetchBalance:
    (nullable void (^)(QoraiRewardsBalance* _Nullable))completion;

/// The users current wallet balance and related info
@property(nonatomic, readonly, nullable) QoraiRewardsBalance* balance;

#pragma mark - Publishers

@property(nonatomic, readonly, getter=isLoadingPublisherList)
    BOOL loadingPublisherList;

/// Get publisher info & its activity based on its publisher key
///
/// This key is _not_ always the URL's host. Use `publisherActivityFromURL`
/// instead when obtaining a publisher given a URL
///
/// @note `completion` callback is called synchronously
- (void)listActivityInfoFromStart:(unsigned int)start
                            limit:(unsigned int)limit
                           filter:(QoraiRewardsActivityInfoFilter*)filter
                       completion:
                           (void (^)(NSArray<QoraiRewardsPublisherInfo*>*))
                               completion;

/// Start a fetch to get a publishers activity information given a URL
///
/// Use `RewardsObserver` to retrieve a panel publisher if one is found
- (void)fetchPublisherActivityFromURL:(NSURL*)URL
                           faviconURL:(nullable NSURL*)faviconURL
                        publisherBlob:(nullable NSString*)publisherBlob
                                tabId:(uint64_t)tabId;

/// Refresh a publishers verification status
- (void)refreshPublisherWithId:(NSString*)publisherId
                    completion:(void (^)(QoraiRewardsPublisherStatus status))
                                   completion;

#pragma mark - Tips

/// Get a list of publishers who the user has recurring tips on
///
/// @note `completion` callback is called synchronously
- (void)listRecurringTips:
    (void (^)(NSArray<QoraiRewardsPublisherInfo*>*))completion;

- (void)removeRecurringTipForPublisherWithId:(NSString*)publisherId
    NS_SWIFT_NAME(removeRecurringTip(publisherId:));

#pragma mark - Misc

- (void)rewardsInternalInfo:
    (void (^)(QoraiRewardsRewardsInternalsInfo* _Nullable info))completion;

- (void)allContributions:
    (void (^)(NSArray<QoraiRewardsContributionInfo*>* contributions))completion;

@property(nonatomic, readonly, copy) NSString* rewardsDatabasePath;

#pragma mark - Preferences

/// The number of seconds before a publisher is added.
- (void)setMinimumVisitDuration:(int)minimumVisitDuration;
/// The minimum number of visits before a publisher is added
- (void)setMinimumNumberOfVisits:(int)minimumNumberOfVisits;
/// A custom user agent for network operations on rewards
@property(nonatomic, copy, nullable) NSString* customUserAgent;

@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_QORAI_REWARDS_QORAI_REWARDS_API_H_
