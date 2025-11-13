/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_API_QORAI_WALLET_QORAI_WALLET_API_H_
#define QORAI_IOS_BROWSER_API_QORAI_WALLET_QORAI_WALLET_API_H_

#import <Foundation/Foundation.h>

@protocol QoraiWalletBlockchainRegistry;
@protocol QoraiWalletEthereumProvider;
@protocol QoraiWalletProviderDelegate;
@protocol QoraiWalletSolanaProvider;
@protocol QoraiWalletQoraiWalletP3A;

typedef NS_ENUM(NSInteger, QoraiWalletCoinType);

NS_ASSUME_NONNULL_BEGIN

typedef NSString* QoraiWalletProviderScriptKey NS_STRING_ENUM;
OBJC_EXPORT QoraiWalletProviderScriptKey const
    QoraiWalletProviderScriptKeyEthereum;
OBJC_EXPORT QoraiWalletProviderScriptKey const
    QoraiWalletProviderScriptKeySolana;
OBJC_EXPORT QoraiWalletProviderScriptKey const
    QoraiWalletProviderScriptKeySolanaWeb3;
OBJC_EXPORT QoraiWalletProviderScriptKey const
    QoraiWalletProviderScriptKeyWalletStandard;

OBJC_EXPORT
@interface QoraiWallet : NSObject
- (instancetype)init NS_UNAVAILABLE;
@end

OBJC_EXPORT
@interface QoraiWalletAPI : NSObject

/// Whether or not the feature is allowed to run in the app
@property(readonly) bool isAllowed;

@property(class, readonly) id<QoraiWalletBlockchainRegistry> blockchainRegistry;

- (nullable id<QoraiWalletEthereumProvider>)
    ethereumProviderWithDelegate:(id<QoraiWalletProviderDelegate>)delegate
               isPrivateBrowsing:(bool)isPrivateBrowsing NS_SWIFT_UI_ACTOR;

- (nullable id<QoraiWalletSolanaProvider>)
    solanaProviderWithDelegate:(id<QoraiWalletProviderDelegate>)delegate
             isPrivateBrowsing:(bool)isPrivateBrowsing NS_SWIFT_UI_ACTOR;

- (NSDictionary<QoraiWalletProviderScriptKey, NSString*>*)
    providerScriptsForCoinType:(QoraiWalletCoinType)coinType;

- (nullable id<QoraiWalletQoraiWalletP3A>)walletP3A;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif  // QORAI_IOS_BROWSER_API_QORAI_WALLET_QORAI_WALLET_API_H_
