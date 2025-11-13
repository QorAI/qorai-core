/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_SYNC_QORAI_SYNC_API_H_
#define QORAI_IOS_BROWSER_API_SYNC_QORAI_SYNC_API_H_

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class QoraiSyncInternalsController;

typedef NSInteger QoraiSyncAPISyncProtocolErrorResult
    NS_TYPED_ENUM NS_SWIFT_NAME(QoraiSyncAPI.SyncProtocolErrorResult);

OBJC_EXPORT QoraiSyncAPISyncProtocolErrorResult const
    QoraiSyncAPISyncProtocolErrorResultSuccess;
OBJC_EXPORT QoraiSyncAPISyncProtocolErrorResult const
    QoraiSyncAPISyncProtocolErrorResultNotMyBirthday;
OBJC_EXPORT QoraiSyncAPISyncProtocolErrorResult const
    QoraiSyncAPISyncProtocolErrorResultThrottled;
OBJC_EXPORT QoraiSyncAPISyncProtocolErrorResult const
    QoraiSyncAPISyncProtocolErrorResultTransientError;
OBJC_EXPORT QoraiSyncAPISyncProtocolErrorResult const
    QoraiSyncAPISyncProtocolErrorResultMigrationDone;
OBJC_EXPORT QoraiSyncAPISyncProtocolErrorResult const
    QoraiSyncAPISyncProtocolErrorResultDisabledByAdmin;
OBJC_EXPORT QoraiSyncAPISyncProtocolErrorResult const
    QoraiSyncAPISyncProtocolErrorResultPartialFailure;
OBJC_EXPORT QoraiSyncAPISyncProtocolErrorResult const
    QoraiSyncAPISyncProtocolErrorResultDataObsolete;
OBJC_EXPORT QoraiSyncAPISyncProtocolErrorResult const
    QoraiSyncAPISyncProtocolErrorResultEncryptionObsolete;
OBJC_EXPORT QoraiSyncAPISyncProtocolErrorResult const
    QoraiSyncAPISyncProtocolErrorResultUnknown;

typedef NSInteger QoraiSyncAPIQrCodeDataValidationResult NS_TYPED_ENUM
    NS_SWIFT_NAME(QoraiSyncAPI.QrCodeDataValidationResult);

OBJC_EXPORT QoraiSyncAPIQrCodeDataValidationResult const
    QoraiSyncAPIQrCodeDataValidationResultValid;
OBJC_EXPORT QoraiSyncAPIQrCodeDataValidationResult const
    QoraiSyncAPIQrCodeDataValidationResultNotWellFormed;
OBJC_EXPORT QoraiSyncAPIQrCodeDataValidationResult const
    QoraiSyncAPIQrCodeDataValidationResultVersionDeprecated;
OBJC_EXPORT QoraiSyncAPIQrCodeDataValidationResult const
    QoraiSyncAPIQrCodeDataValidationResultExpired;
OBJC_EXPORT QoraiSyncAPIQrCodeDataValidationResult const
    QoraiSyncAPIQrCodeDataValidationResultValidForTooLong;

typedef NSInteger QoraiSyncAPIWordsValidationStatus NS_TYPED_ENUM
    NS_SWIFT_NAME(QoraiSyncAPI.WordsValidationStatus);

OBJC_EXPORT QoraiSyncAPIWordsValidationStatus const
    QoraiSyncAPIWordsValidationStatusValid;
OBJC_EXPORT QoraiSyncAPIWordsValidationStatus const
    QoraiSyncAPIWordsValidationStatusNotValidPureWords;
OBJC_EXPORT QoraiSyncAPIWordsValidationStatus const
    QoraiSyncAPIWordsValidationStatusVersionDeprecated;
OBJC_EXPORT QoraiSyncAPIWordsValidationStatus const
    QoraiSyncAPIWordsValidationStatusExpired;
OBJC_EXPORT QoraiSyncAPIWordsValidationStatus const
    QoraiSyncAPIWordsValidationStatusValidForTooLong;
OBJC_EXPORT QoraiSyncAPIWordsValidationStatus const
    QoraiSyncAPIWordsValidationStatusWrongWordsNumber;

OBJC_EXPORT
@interface QoraiSyncAPI : NSObject

@property(nonatomic, readonly) bool canSyncFeatureStart;
@property(nonatomic, readonly) bool isSyncFeatureActive;
@property(nonatomic, readonly) bool isInitialSyncFeatureSetupComplete;
@property(nonatomic) bool isSyncAccountDeletedNoticePending;
@property(nonatomic, readonly) bool isFailedDecryptSeedNoticeDismissed;
@property(readonly) bool isInSyncGroup;

- (instancetype)init NS_UNAVAILABLE;

- (void)requestSync;

- (void)setSetupComplete;

- (void)resetSync;

- (void)setDidJoinSyncChain:(void (^)(bool))completion;

- (void)permanentlyDeleteAccount:
    (void (^)(QoraiSyncAPISyncProtocolErrorResult))completion;

- (void)deleteDevice:(NSString*)guid;

- (bool)isValidSyncCode:(NSString*)syncCode;

- (NSString*)getSyncCode;

// returns false is sync is already configured or if the sync code is invalid
- (bool)setSyncCode:(NSString*)syncCode;

- (NSString*)syncCodeFromHexSeed:(NSString*)hexSeed;

- (NSString*)hexSeedFromSyncCode:(NSString*)syncCode;

- (NSString*)qrCodeJsonFromHexSeed:(NSString*)hexSeed;

- (void)dismissFailedDecryptSeedNotice;

- (QoraiSyncAPIQrCodeDataValidationResult)getQRCodeValidationResult:
    (NSString*)json;

- (QoraiSyncAPIWordsValidationStatus)getWordsValidationResult:
    (NSString*)timeLimitedWords;

- (NSString*)getWordsFromTimeLimitedWords:(NSString*)timeLimitedWords;

- (NSString*)getTimeLimitedWordsFromWords:(NSString*)words;

- (NSDate*)getExpirationFromTimeLimitedWords:(NSString*)timeLimitedWords;

- (NSString*)getHexSeedFromQrCodeJson:(NSString*)json;

- (nullable UIImage*)getQRCodeImage:(CGSize)size;

- (nullable NSString*)getDeviceListJSON;

- (id)createSyncDeviceObserver:(void (^)())onDeviceInfoChanged;
- (id)createSyncServiceObserver:(void (^)())onSyncServiceStateChanged
          onSyncServiceShutdown:(void (^)())onSyncServiceShutdown;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_SYNC_QORAI_SYNC_API_H_
