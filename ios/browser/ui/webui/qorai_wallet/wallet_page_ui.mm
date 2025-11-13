// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/ios/browser/ui/webui/qorai_wallet/wallet_page_ui.h"

#include <string>
#include <string_view>
#include <utility>

#include "base/command_line.h"
#include "qorai/components/qorai_wallet/browser/asset_ratio_service.h"
#include "qorai/components/qorai_wallet/browser/blockchain_registry.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_constants.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_ipfs_service.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/json_rpc_service.h"
#include "qorai/components/qorai_wallet/browser/keyring_service.h"
#include "qorai/components/qorai_wallet/browser/meld_integration_service.h"
#include "qorai/components/qorai_wallet/browser/simulation_service.h"
#include "qorai/components/qorai_wallet/browser/swap_service.h"
#include "qorai/components/qorai_wallet/browser/tx_service.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "qorai/components/qorai_wallet_page/resources/grit/qorai_wallet_page_generated_map.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "qorai/ios/browser/qorai_wallet/asset_ratio_service_factory.h"
#include "qorai/ios/browser/qorai_wallet/qorai_wallet_ipfs_service_factory.h"
#include "qorai/ios/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "qorai/ios/browser/qorai_wallet/meld_integration_service_factory.h"
#include "qorai/ios/browser/qorai_wallet/swap_service_factory.h"
#include "qorai/ios/browser/ui/webui/sanitized_image_source.h"
#include "qorai/ios/web/webui/qorai_web_ui_ios_data_source.h"
#include "qorai/ios/web/webui/qorai_webui_utils.h"
#include "components/grit/qorai_components_resources.h"
#include "ios/chrome/browser/shared/model/profile/profile_ios.h"
#include "ios/web/public/web_state.h"

namespace {
// Content-Security-Policy: frame-src chrome-untrusted://trezor-bridge/
// chrome-untrusted://ledger-bridge/ chrome-untrusted://nft-display/
// chrome-untrusted://line-chart-display/ chrome-untrusted://market-display/;
// fails to work unless all the trailing slashes from each policy.
// For some reason, on Desktop, the trailing slashes don't seem to matter???
// So for iOS, this function will strip the trailing slashes so the CSPs apply
// correctly
std::string StripTrailingSlash(std::string_view url) {
  std::string result(url);
  base::TrimString(result, "/", &result);
  return result;
}
}  // namespace

WalletPageUI::WalletPageUI(web::WebUIIOS* web_ui, const GURL& url)
    : web::WebUIIOSController(web_ui, url.host()) {
  // Create a URLDataSource and add resources.

  QoraiWebUIIOSDataSource* source = qorai::CreateAndAddWebUIDataSource(
      web_ui, url.host(), kQoraiWalletPageGenerated, IDR_WALLET_PAGE_HTML);

  source->AddLocalizedStrings(qorai_wallet::kLocalizedStrings);

  source->AddBoolean("isMobile", true);
  source->AddString("qoraiWalletLedgerBridgeUrl", kUntrustedLedgerURL);
  source->AddString("qoraiWalletTrezorBridgeUrl", kUntrustedTrezorURL);
  source->AddString("qoraiWalletNftBridgeUrl", kUntrustedNftURL);
  source->AddString("qoraiWalletLineChartBridgeUrl", kUntrustedLineChartURL);
  source->AddString("qoraiWalletMarketUiBridgeUrl", kUntrustedMarketURL);
  source->AddBoolean(qorai_wallet::mojom::kP3ACountTestNetworksLoadTimeKey,
                     base::CommandLine::ForCurrentProcess()->HasSwitch(
                         qorai_wallet::mojom::kP3ACountTestNetworksSwitch));

  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::FrameSrc,
      std::string("frame-src ") + StripTrailingSlash(kUntrustedTrezorURL) +
          " " + StripTrailingSlash(kUntrustedLedgerURL) + " " +
          StripTrailingSlash(kUntrustedNftURL) + " " +
          StripTrailingSlash(kUntrustedLineChartURL) + " " +
          StripTrailingSlash(kUntrustedMarketURL) + ";");

  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::ImgSrc,
      base::JoinString({"img-src", "'self'", "chrome://resources",
                        "chrome://erc-token-images", "chrome://image",
                        base::StrCat({"data:", ";"})},
                       " "));

  auto* profile = ProfileIOS::FromWebUIIOS(web_ui);
  web::URLDataSourceIOS::Add(profile, new SanitizedImageSource(profile));

  web_ui->GetWebState()->GetInterfaceBinderForMainFrame()->AddInterface(
      base::BindRepeating(&WalletPageUI::BindInterface,
                          base::Unretained(this)));
}

WalletPageUI::~WalletPageUI() {
  web_ui()->GetWebState()->GetInterfaceBinderForMainFrame()->RemoveInterface(
      qorai_wallet::mojom::PageHandlerFactory::Name_);
}

void WalletPageUI::BindInterface(
    mojo::PendingReceiver<qorai_wallet::mojom::PageHandlerFactory> receiver) {
  page_factory_receiver_.reset();
  page_factory_receiver_.Bind(std::move(receiver));
}

void WalletPageUI::CreatePageHandler(
    mojo::PendingReceiver<qorai_wallet::mojom::PageHandler> page_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::WalletHandler> wallet_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::JsonRpcService> json_rpc_service,
    mojo::PendingReceiver<qorai_wallet::mojom::BitcoinWalletService>
        bitcoin_rpc_service,
    mojo::PendingReceiver<qorai_wallet::mojom::PolkadotWalletService>
        polkadot_wallet_service,
    mojo::PendingReceiver<qorai_wallet::mojom::ZCashWalletService>
        zcash_service,
    mojo::PendingReceiver<qorai_wallet::mojom::CardanoWalletService>
        cardano_wallet_service_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::SwapService> swap_service,
    mojo::PendingReceiver<qorai_wallet::mojom::AssetRatioService>
        asset_ratio_service,
    mojo::PendingReceiver<qorai_wallet::mojom::KeyringService> keyring_service,
    mojo::PendingReceiver<qorai_wallet::mojom::BlockchainRegistry>
        blockchain_registry_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::TxService> tx_service,
    mojo::PendingReceiver<qorai_wallet::mojom::EthTxManagerProxy>
        eth_tx_manager_proxy,
    mojo::PendingReceiver<qorai_wallet::mojom::SolanaTxManagerProxy>
        solana_tx_manager_proxy,
    mojo::PendingReceiver<qorai_wallet::mojom::FilTxManagerProxy>
        filecoin_tx_manager_proxy,
    mojo::PendingReceiver<qorai_wallet::mojom::BtcTxManagerProxy>
        bitcoin_tx_manager_proxy_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::QoraiWalletService>
        qorai_wallet_service,
    mojo::PendingReceiver<qorai_wallet::mojom::QoraiWalletP3A> qorai_wallet_p3a,
    mojo::PendingReceiver<qorai_wallet::mojom::IpfsService>
        qorai_wallet_ipfs_service_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::MeldIntegrationService>
        meld_integration_service) {
  auto* profile = ProfileIOS::FromWebUIIOS(web_ui());
  DCHECK(profile);

  page_handler_ = std::make_unique<WalletPageHandler>(web_ui()->GetWebState(),
                                                      std::move(page_receiver));

  if (auto* wallet_service =
          qorai_wallet::QoraiWalletServiceFactory::GetServiceForState(
              profile)) {
    wallet_service->Bind(std::move(qorai_wallet_service));
    wallet_service->Bind(std::move(json_rpc_service));
    wallet_service->Bind(std::move(bitcoin_rpc_service));
    wallet_service->Bind(std::move(polkadot_wallet_service));
    wallet_service->Bind(std::move(zcash_service));
    wallet_service->Bind(std::move(cardano_wallet_service_receiver));
    wallet_service->Bind(std::move(keyring_service));
    wallet_service->Bind(std::move(tx_service));
    wallet_service->Bind(std::move(eth_tx_manager_proxy));
    wallet_service->Bind(std::move(solana_tx_manager_proxy));
    wallet_service->Bind(std::move(filecoin_tx_manager_proxy));
    wallet_service->Bind(std::move(bitcoin_tx_manager_proxy_receiver));
    wallet_service->Bind(std::move(qorai_wallet_p3a));
    wallet_handler_ = std::make_unique<qorai_wallet::WalletHandler>(
        std::move(wallet_receiver), wallet_service);
  }

  qorai_wallet::SwapServiceFactory::GetServiceForProfile(profile)->Bind(
      std::move(swap_service));
  qorai_wallet::AssetRatioServiceFactory::GetServiceForState(profile)->Bind(
      std::move(asset_ratio_service));
  qorai_wallet::MeldIntegrationServiceFactory::GetServiceForState(profile)
      ->Bind(std::move(meld_integration_service));
  qorai_wallet::QoraiWalletIpfsServiceFactory::GetServiceForState(profile)
      ->Bind(std::move(qorai_wallet_ipfs_service_receiver));

  if (auto* blockchain_registry =
          qorai_wallet::BlockchainRegistry::GetInstance()) {
    blockchain_registry->Bind(std::move(blockchain_registry_receiver));
  }
}
