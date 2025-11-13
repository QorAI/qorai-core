/* Copyright (c) 2020 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "qorai/ios/browser/api/qorai_wallet/qorai_wallet_api.h"

#include "base/memory/raw_ptr.h"
#include "base/strings/sys_string_conversions.h"
#include "qorai/components/qorai_wallet/browser/blockchain_registry.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_p3a.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/ethereum_provider_impl.h"
#include "qorai/components/qorai_wallet/browser/solana_provider_impl.h"
#include "qorai/components/qorai_wallet/common/common_utils.h"
#include "qorai/components/qorai_wallet/resources/grit/qorai_wallet_script_generated.h"
#include "qorai/ios/browser/api/qorai_wallet/qorai_wallet.mojom.objc+private.h"
#include "qorai/ios/browser/api/qorai_wallet/qorai_wallet_provider_delegate_ios+private.h"
#include "qorai/ios/browser/api/qorai_wallet/qorai_wallet_provider_delegate_ios.h"
#include "qorai/ios/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "components/grit/qorai_components_resources.h"
#include "ios/chrome/browser/content_settings/model/host_content_settings_map_factory.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"
#include "ios/chrome/browser/shared/model/profile/profile_manager_ios.h"
#include "ios/web/public/thread/web_thread.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "ui/base/resource/resource_bundle.h"

QoraiWalletProviderScriptKey const QoraiWalletProviderScriptKeyEthereum =
    @"ethereum_provider.js";
QoraiWalletProviderScriptKey const QoraiWalletProviderScriptKeySolana =
    @"solana_provider.js";
QoraiWalletProviderScriptKey const QoraiWalletProviderScriptKeySolanaWeb3 =
    @"solana_web3.js";
QoraiWalletProviderScriptKey const QoraiWalletProviderScriptKeyWalletStandard =
    @"wallet_standard.js";

#if !defined(__has_feature) || !__has_feature(objc_arc)
#error "This file requires ARC support."
#endif

@implementation QoraiWallet
@end

@implementation QoraiWalletAPI {
  raw_ptr<ProfileIOS> _profile;  // NOT OWNED
  NSMutableDictionary<NSNumber* /* QoraiWalletCoinType */,
                      NSDictionary<QoraiWalletProviderScriptKey, NSString*>*>*
      _providerScripts;
}

- (instancetype)initWithBrowserState:(ProfileIOS*)profile {
  if ((self = [super init])) {
    _profile = profile;
    _providerScripts = [[NSMutableDictionary alloc] init];
  }
  return self;
}

- (bool)isAllowed {
  return qorai_wallet::IsAllowed(_profile->GetPrefs());
}

+ (id<QoraiWalletBlockchainRegistry>)blockchainRegistry {
  auto* registry = qorai_wallet::BlockchainRegistry::GetInstance();
  return [[QoraiWalletBlockchainRegistryMojoImpl alloc]
      initWithBlockchainRegistry:registry->MakeRemote()];
}

- (nullable id<QoraiWalletEthereumProvider>)
    ethereumProviderWithDelegate:(id<QoraiWalletProviderDelegate>)delegate
               isPrivateBrowsing:(bool)isPrivateBrowsing {
  DCHECK_CURRENTLY_ON(web::WebThread::UI);
  auto* profile = _profile.get();
  if (isPrivateBrowsing) {
    profile = profile->GetOffTheRecordProfile();
  }

  auto* qorai_wallet_service =
      qorai_wallet::QoraiWalletServiceFactory::GetServiceForState(profile);
  if (!qorai_wallet_service) {
    return nil;
  }

  auto provider = std::make_unique<qorai_wallet::EthereumProviderImpl>(
      ios::HostContentSettingsMapFactory::GetForProfile(profile),
      qorai_wallet_service,
      std::make_unique<qorai_wallet::QoraiWalletProviderDelegateBridge>(
          delegate),
      profile->GetPrefs());
  return [[QoraiWalletEthereumProviderMojoImpl alloc]
      initWithEthereumProviderImpl:std::move(provider)];
}

- (nullable id<QoraiWalletSolanaProvider>)
    solanaProviderWithDelegate:(id<QoraiWalletProviderDelegate>)delegate
             isPrivateBrowsing:(bool)isPrivateBrowsing {
  DCHECK_CURRENTLY_ON(web::WebThread::UI);
  auto* profile = _profile.get();
  if (isPrivateBrowsing) {
    profile = profile->GetOffTheRecordProfile();
  }

  auto* qorai_wallet_service =
      qorai_wallet::QoraiWalletServiceFactory::GetServiceForState(profile);
  if (!qorai_wallet_service) {
    return nil;
  }

  auto* host_content_settings_map =
      ios::HostContentSettingsMapFactory::GetForProfile(profile);
  if (!host_content_settings_map) {
    return nil;
  }

  auto provider = std::make_unique<qorai_wallet::SolanaProviderImpl>(
      *host_content_settings_map, qorai_wallet_service,
      std::make_unique<qorai_wallet::QoraiWalletProviderDelegateBridge>(
          delegate));
  return [[QoraiWalletSolanaProviderMojoImpl alloc]
      initWithSolanaProviderImpl:std::move(provider)];
}

- (NSString*)resourceForID:(int)resource_id {
  // The resource bundle is not available until after WebMainParts is setup
  auto& resource_bundle = ui::ResourceBundle::GetSharedInstance();
  std::string resource_string = "";
  if (resource_bundle.IsGzipped(resource_id)) {
    resource_string =
        std::string(resource_bundle.LoadDataResourceString(resource_id));
  } else {
    resource_string =
        std::string(resource_bundle.GetRawDataResource(resource_id));
  }
  return base::SysUTF8ToNSString(resource_string);
}

- (NSDictionary<QoraiWalletProviderScriptKey, NSString*>*)
    providerScriptsForCoinType:(QoraiWalletCoinType)coinType {
  auto cachedScript = _providerScripts[@(coinType)];
  if (cachedScript) {
    return cachedScript;
  }
  auto resource_ids =
      ^std::vector<std::pair<QoraiWalletProviderScriptKey, int>> {
    switch (coinType) {
      case QoraiWalletCoinTypeEth:
        return {std::make_pair(
            QoraiWalletProviderScriptKeyEthereum,
            IDR_QORAI_WALLET_SCRIPT_ETHEREUM_PROVIDER_SCRIPT_BUNDLE_JS)};
      case QoraiWalletCoinTypeSol:
        return {std::make_pair(
                    QoraiWalletProviderScriptKeySolana,
                    IDR_QORAI_WALLET_SCRIPT_SOLANA_PROVIDER_SCRIPT_BUNDLE_JS),
                std::make_pair(QoraiWalletProviderScriptKeySolanaWeb3,
                               IDR_QORAI_WALLET_SOLANA_WEB3_JS),
                std::make_pair(QoraiWalletProviderScriptKeyWalletStandard,
                               IDR_QORAI_WALLET_STANDARD_JS)};
      case QoraiWalletCoinTypeFil:
        // Currently not supported
        return {std::make_pair(@"", 0)};
      case QoraiWalletCoinTypeBtc:
        // Currently not supported
        return {std::make_pair(@"", 0)};
      case QoraiWalletCoinTypeZec:
        // Currently not supported
        return {std::make_pair(@"", 0)};
      case QoraiWalletCoinTypeAda:
        // Currently not supported
        return {std::make_pair(@"", 0)};
      case QoraiWalletCoinTypeDot:
        // Currently not supported
        return {std::make_pair(@"", 0)};
    }
    return {std::make_pair(@"", 0)};
  }
  ();
  const auto scripts = [[NSMutableDictionary alloc] init];
  for (auto resource : resource_ids) {
    auto key = resource.first;
    auto resource_id = resource.second;
    scripts[key] = [self resourceForID:resource_id];
  }
  _providerScripts[@(coinType)] = [scripts copy];
  return scripts;
}

- (nullable id<QoraiWalletQoraiWalletP3A>)walletP3A {
  auto* service =
      qorai_wallet::QoraiWalletServiceFactory::GetServiceForState(_profile);
  if (!service) {
    return nil;
  }

  mojo::PendingRemote<qorai_wallet::mojom::QoraiWalletP3A> pending_remote;
  service->Bind(pending_remote.InitWithNewPipeAndPassReceiver());
  return [[QoraiWalletQoraiWalletP3AMojoImpl alloc]
      initWithQoraiWalletP3A:std::move(pending_remote)];
}

@end
