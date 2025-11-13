/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef QORAI_IOS_BROWSER_QORAI_WALLET_QORAI_WALLET_FACTORY_WRAPPERS_H_
#define QORAI_IOS_BROWSER_QORAI_WALLET_QORAI_WALLET_FACTORY_WRAPPERS_H_

#import <Foundation/Foundation.h>
#include "keyed_service_factory_wrapper.h"  // NOLINT

@protocol QoraiWalletAssetRatioService
, QoraiWalletQoraiWalletService, QoraiWalletBitcoinWalletService,
    QoraiWalletJsonRpcService, QoraiWalletEthTxManagerProxy,
    QoraiWalletSolanaTxManagerProxy, QoraiWalletTxService,
    QoraiWalletKeyringService, QoraiWalletMeldIntegrationService,
    QoraiWalletSwapService, QoraiWalletIpfsService,
    QoraiWalletZCashWalletService;

OBJC_EXPORT
NS_SWIFT_NAME(QoraiWallet.AssetRatioServiceFactory)
@interface QoraiWalletAssetRatioServiceFactory
    : KeyedServiceFactoryWrapper <id <QoraiWalletAssetRatioService>>
@end

OBJC_EXPORT
NS_SWIFT_NAME(QoraiWallet.BitcoinWalletServiceFactory)
@interface QoraiWalletBitcoinWalletServiceFactory
    : KeyedServiceFactoryWrapper <id <QoraiWalletBitcoinWalletService>>
@end

OBJC_EXPORT
NS_SWIFT_NAME(QoraiWallet.JsonRpcServiceFactory)
@interface QoraiWalletJsonRpcServiceFactory
    : KeyedServiceFactoryWrapper <id <QoraiWalletJsonRpcService>>
@end

OBJC_EXPORT
NS_SWIFT_NAME(QoraiWallet.TxServiceFactory)
@interface QoraiWalletTxServiceFactory
    : KeyedServiceFactoryWrapper <id <QoraiWalletTxService>>
@end

OBJC_EXPORT
NS_SWIFT_NAME(QoraiWallet.EthTxManagerProxyFactory)
@interface QoraiWalletEthTxManagerProxyFactory
    : KeyedServiceFactoryWrapper <id <QoraiWalletEthTxManagerProxy>>
@end

OBJC_EXPORT
NS_SWIFT_NAME(QoraiWallet.SolanaTxManagerProxyFactory)
@interface QoraiWalletSolanaTxManagerProxyFactory
    : KeyedServiceFactoryWrapper <id <QoraiWalletSolanaTxManagerProxy>>
@end

OBJC_EXPORT
NS_SWIFT_NAME(QoraiWallet.KeyringServiceFactory)
@interface QoraiWalletKeyringServiceFactory
    : KeyedServiceFactoryWrapper <id <QoraiWalletKeyringService>>
@end

OBJC_EXPORT
NS_SWIFT_NAME(QoraiWallet.MeldIntegrationServiceFactory)
@interface QoraiWalletMeldIntegrationServiceFactory
    : KeyedServiceFactoryWrapper <id <QoraiWalletMeldIntegrationService>>
@end

OBJC_EXPORT
NS_SWIFT_NAME(QoraiWallet.ServiceFactory)
@interface QoraiWalletServiceFactory
    : KeyedServiceFactoryWrapper <id <QoraiWalletQoraiWalletService>>
@end

OBJC_EXPORT
NS_SWIFT_NAME(QoraiWallet.SwapServiceFactory)
@interface QoraiWalletSwapServiceFactory
    : KeyedServiceFactoryWrapper <id <QoraiWalletSwapService>>
@end

OBJC_EXPORT
NS_SWIFT_NAME(QoraiWallet.IpfsServiceFactory)
@interface QoraiWalletIpfsServiceFactory
    : KeyedServiceFactoryWrapper <id <QoraiWalletIpfsService>>
@end

OBJC_EXPORT
NS_SWIFT_NAME(QoraiWallet.ZCashWalletServiceFactory)
@interface QoraiWalletZCashWalletServiceFactory
    : KeyedServiceFactoryWrapper <id <QoraiWalletZCashWalletService>>
@end

#endif  // QORAI_IOS_BROWSER_QORAI_WALLET_QORAI_WALLET_FACTORY_WRAPPERS_H_
