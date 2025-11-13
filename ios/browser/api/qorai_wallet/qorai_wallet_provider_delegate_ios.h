/* Copyright (c) 2022 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_QORAI_WALLET_QORAI_WALLET_PROVIDER_DELEGATE_IOS_H_
#define QORAI_IOS_BROWSER_API_QORAI_WALLET_QORAI_WALLET_PROVIDER_DELEGATE_IOS_H_

#import <Foundation/Foundation.h>
#import "qorai_wallet.mojom.objc.h"

@class URLOriginIOS;

NS_ASSUME_NONNULL_BEGIN

typedef void (^RequestPermissionsCallback)(
    QoraiWalletRequestPermissionsError error,
    NSArray<NSString*>* _Nullable allowedAccounts);

OBJC_EXPORT
@protocol QoraiWalletProviderDelegate
- (bool)isTabVisible;
- (void)showPanel;
- (URLOriginIOS*)getOrigin;
- (void)walletInteractionDetected;
- (void)showWalletOnboarding;
- (void)showWalletBackup;
- (void)unlockWallet;
- (void)showAccountCreation:(QoraiWalletCoinType)type;
- (void)requestPermissions:(QoraiWalletCoinType)type
                  accounts:(NSArray<NSString*>*)accounts
                completion:(RequestPermissionsCallback)completion;
- (bool)isAccountAllowed:(QoraiWalletCoinType)type account:(NSString*)account;
- (nullable NSArray<NSString*>*)getAllowedAccounts:(QoraiWalletCoinType)type
                                          accounts:
                                              (NSArray<NSString*>*)accounts;
- (bool)isPermissionDenied:(QoraiWalletCoinType)type;
- (void)addSolanaConnectedAccount:(NSString*)account;
- (void)removeSolanaConnectedAccount:(NSString*)account;
- (bool)isSolanaAccountConnected:(NSString*)account;
@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_QORAI_WALLET_QORAI_WALLET_PROVIDER_DELEGATE_IOS_H_
