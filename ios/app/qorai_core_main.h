/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_APP_QORAI_CORE_MAIN_H_
#define QORAI_IOS_APP_QORAI_CORE_MAIN_H_

#import <Foundation/Foundation.h>

#import "qorai_core_switches.h"  // NOLINT

@class QoraiP3AUtils;
@class AdblockService;
@class HTTPSUpgradeExceptionsService;
@class QoraiUserAgentExceptionsIOS;
@class QoraiProfileController;
@protocol PrefServiceBridge;

NS_ASSUME_NONNULL_BEGIN

typedef int QoraiCoreLogSeverity NS_TYPED_ENUM;
OBJC_EXPORT const QoraiCoreLogSeverity QoraiCoreLogSeverityFatal;
OBJC_EXPORT const QoraiCoreLogSeverity QoraiCoreLogSeverityError;
OBJC_EXPORT const QoraiCoreLogSeverity QoraiCoreLogSeverityWarning;
OBJC_EXPORT const QoraiCoreLogSeverity QoraiCoreLogSeverityInfo;
OBJC_EXPORT const QoraiCoreLogSeverity QoraiCoreLogSeverityVerbose;

typedef bool (^QoraiCoreLogHandler)(QoraiCoreLogSeverity severity,
                                    NSString* file,
                                    int line,
                                    size_t messageStart,
                                    NSString* formattedMessage);

OBJC_EXPORT
@interface QoraiCoreMain : NSObject

@property(nonatomic, readonly)
    HTTPSUpgradeExceptionsService* httpsUpgradeExceptionsService;

@property(nonatomic, readonly, nullable)
    QoraiUserAgentExceptionsIOS* qoraiUserAgentExceptions;

/// Sets the global log handler for Chromium & QoraiCore logs.
///
/// When a custom log handler is set, it is the responsibility of the client
/// to handle fatal logs from CHECK (and DCHECK on debug builds) by checking
/// the `serverity` passed in.
+ (void)setLogHandler:(nullable QoraiCoreLogHandler)logHandler;

- (instancetype)init;

- (instancetype)initWithAdditionalSwitches:
    (NSArray<QoraiCoreSwitch*>*)additionalSwitches;

- (void)scheduleLowPriorityStartupTasks;

- (void)setUserAgent:(NSString*)userAgent;

@property(readonly) AdblockService* adblockService;

- (void)initializeP3AServiceForChannel:(NSString*)channel
                      installationDate:(NSDate*)installDate;

@property(readonly) QoraiP3AUtils* p3aUtils;

@property(readonly) id<PrefServiceBridge> localState;

@property(readonly, nullable) QoraiProfileController* profileController;
- (void)loadDefaultProfile:(void (^)(QoraiProfileController*))completionHandler;

/// Sets up bundle path overrides and initializes ICU from the QoraiCore bundle
/// without setting up a QoraiCoreMain instance.
///
/// Should only be called in unit tests
+ (bool)initializeICUForTesting;

+ (void)initializeResourceBundleForTesting;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_APP_QORAI_CORE_MAIN_H_
