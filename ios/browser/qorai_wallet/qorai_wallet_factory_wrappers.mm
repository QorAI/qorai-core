/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/ios/browser/qorai_wallet/qorai_wallet_factory_wrappers.h"

#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/json_rpc_service.h"
#include "qorai/components/qorai_wallet/browser/keyring_service.h"
#include "qorai/components/qorai_wallet/browser/tx_service.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/ios/browser/api/qorai_wallet/qorai_wallet.mojom.objc+private.h"
#include "qorai/ios/browser/qorai_wallet/asset_ratio_service_factory.h"
#include "qorai/ios/browser/qorai_wallet/qorai_wallet_ipfs_service_factory.h"
#include "qorai/ios/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "qorai/ios/browser/qorai_wallet/meld_integration_service_factory.h"
#include "qorai/ios/browser/qorai_wallet/swap_service_factory.h"
#include "qorai/ios/browser/keyed_service/keyed_service_factory_wrapper+private.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"

#if !defined(__has_feature) || !__has_feature(objc_arc)
#error "This file requires ARC support."
#endif

@implementation QoraiWalletAssetRatioServiceFactory
+ (nullable id)serviceForProfile:(ProfileIOS*)profile {
  auto service = qorai_wallet::AssetRatioServiceFactory::GetForProfile(profile);
  if (!service) {
    return nil;
  }
  return [[QoraiWalletAssetRatioServiceMojoImpl alloc]
      initWithAssetRatioService:std::move(service)];
}
@end

@implementation QoraiWalletBitcoinWalletServiceFactory
+ (nullable id)serviceForProfile:(ProfileIOS*)profile {
  auto* qorai_wallet_service =
      qorai_wallet::QoraiWalletServiceFactory::GetServiceForState(profile);
  if (!qorai_wallet_service) {
    return nil;
  }
  mojo::PendingRemote<qorai_wallet::mojom::BitcoinWalletService> pending_remote;
  qorai_wallet_service->Bind(pending_remote.InitWithNewPipeAndPassReceiver());
  return [[QoraiWalletBitcoinWalletServiceMojoImpl alloc]
      initWithBitcoinWalletService:std::move(pending_remote)];
}

@end

@implementation QoraiWalletJsonRpcServiceFactory
+ (nullable id)serviceForProfile:(ProfileIOS*)profile {
  auto* qorai_wallet_service =
      qorai_wallet::QoraiWalletServiceFactory::GetServiceForState(profile);
  if (!qorai_wallet_service) {
    return nil;
  }
  mojo::PendingRemote<qorai_wallet::mojom::JsonRpcService> pending_remote;
  qorai_wallet_service->Bind(pending_remote.InitWithNewPipeAndPassReceiver());
  return [[QoraiWalletJsonRpcServiceMojoImpl alloc]
      initWithJsonRpcService:std::move(pending_remote)];
}
@end

@implementation QoraiWalletTxServiceFactory
+ (nullable id)serviceForProfile:(ProfileIOS*)profile {
  auto* qorai_wallet_service =
      qorai_wallet::QoraiWalletServiceFactory::GetServiceForState(profile);
  if (!qorai_wallet_service) {
    return nil;
  }
  mojo::PendingRemote<qorai_wallet::mojom::TxService> pending_remote;
  qorai_wallet_service->Bind(pending_remote.InitWithNewPipeAndPassReceiver());
  return [[QoraiWalletTxServiceMojoImpl alloc]
      initWithTxService:std::move(pending_remote)];
}
@end

@implementation QoraiWalletEthTxManagerProxyFactory
+ (nullable id)serviceForProfile:(ProfileIOS*)profile {
  auto* qorai_wallet_service =
      qorai_wallet::QoraiWalletServiceFactory::GetServiceForState(profile);
  if (!qorai_wallet_service) {
    return nil;
  }
  mojo::PendingRemote<qorai_wallet::mojom::EthTxManagerProxy> pending_remote;
  qorai_wallet_service->Bind(pending_remote.InitWithNewPipeAndPassReceiver());
  return [[QoraiWalletEthTxManagerProxyMojoImpl alloc]
      initWithEthTxManagerProxy:std::move(pending_remote)];
}
@end

@implementation QoraiWalletSolanaTxManagerProxyFactory
+ (nullable id)serviceForProfile:(ProfileIOS*)profile {
  auto* qorai_wallet_service =
      qorai_wallet::QoraiWalletServiceFactory::GetServiceForState(profile);
  if (!qorai_wallet_service) {
    return nil;
  }
  mojo::PendingRemote<qorai_wallet::mojom::SolanaTxManagerProxy> pending_remote;
  qorai_wallet_service->Bind(pending_remote.InitWithNewPipeAndPassReceiver());
  return [[QoraiWalletSolanaTxManagerProxyMojoImpl alloc]
      initWithSolanaTxManagerProxy:std::move(pending_remote)];
}
@end

@implementation QoraiWalletKeyringServiceFactory
+ (nullable id)serviceForProfile:(ProfileIOS*)profile {
  auto* qorai_wallet_service =
      qorai_wallet::QoraiWalletServiceFactory::GetServiceForState(profile);
  if (!qorai_wallet_service) {
    return nil;
  }
  mojo::PendingRemote<qorai_wallet::mojom::KeyringService> pending_remote;
  qorai_wallet_service->Bind(pending_remote.InitWithNewPipeAndPassReceiver());
  return [[QoraiWalletKeyringServiceMojoImpl alloc]
      initWithKeyringService:std::move(pending_remote)];
}
@end

@implementation QoraiWalletMeldIntegrationServiceFactory
+ (nullable id)serviceForProfile:(ProfileIOS*)profile {
  auto service =
      qorai_wallet::MeldIntegrationServiceFactory::GetForProfile(profile);
  if (!service) {
    return nil;
  }
  return [[QoraiWalletMeldIntegrationServiceMojoImpl alloc]
      initWithMeldIntegrationService:std::move(service)];
}
@end

@implementation QoraiWalletServiceFactory
+ (nullable id)serviceForProfile:(ProfileIOS*)profile {
  auto* qorai_wallet_service =
      qorai_wallet::QoraiWalletServiceFactory::GetServiceForState(profile);
  if (!qorai_wallet_service) {
    return nil;
  }
  mojo::PendingRemote<qorai_wallet::mojom::QoraiWalletService> pending_remote;
  qorai_wallet_service->Bind(pending_remote.InitWithNewPipeAndPassReceiver());
  return [[QoraiWalletQoraiWalletServiceMojoImpl alloc]
      initWithQoraiWalletService:std::move(pending_remote)];
}
@end

@implementation QoraiWalletSwapServiceFactory
+ (nullable id)serviceForProfile:(ProfileIOS*)profile {
  auto service = qorai_wallet::SwapServiceFactory::GetForProfile(profile);
  if (!service) {
    return nil;
  }
  return [[QoraiWalletSwapServiceMojoImpl alloc]
      initWithSwapService:std::move(service)];
}
@end

@implementation QoraiWalletIpfsServiceFactory
+ (nullable id)serviceForProfile:(ProfileIOS*)profile {
  auto service =
      qorai_wallet::QoraiWalletIpfsServiceFactory::GetForProfile(profile);
  if (!service) {
    return nil;
  }
  return [[QoraiWalletIpfsServiceMojoImpl alloc]
      initWithIpfsService:std::move(service)];
}
@end

@implementation QoraiWalletZCashWalletServiceFactory
+ (nullable id)serviceForProfile:(ProfileIOS*)profile {
  auto* qorai_wallet_service =
      qorai_wallet::QoraiWalletServiceFactory::GetServiceForState(profile);
  if (!qorai_wallet_service) {
    return nil;
  }
  mojo::PendingRemote<qorai_wallet::mojom::ZCashWalletService> pending_remote;
  qorai_wallet_service->Bind(pending_remote.InitWithNewPipeAndPassReceiver());
  return [[QoraiWalletZCashWalletServiceMojoImpl alloc]
      initWithZCashWalletService:std::move(pending_remote)];
}
@end
