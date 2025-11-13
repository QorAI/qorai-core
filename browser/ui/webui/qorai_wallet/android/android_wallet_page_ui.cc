// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "qorai/browser/ui/webui/qorai_wallet/android/android_wallet_page_ui.h"

#include <utility>

#include "base/check.h"
#include "base/command_line.h"
#include "base/strings/string_util.h"
#include "qorai/browser/qorai_wallet/asset_ratio_service_factory.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_ipfs_service_factory.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_provider_delegate_impl_helper.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "qorai/browser/qorai_wallet/meld_integration_service_factory.h"
#include "qorai/browser/qorai_wallet/swap_service_factory.h"
#include "qorai/browser/ui/webui/qorai_wallet/wallet_common_ui.h"
#include "qorai/browser/ui/webui/qorai_webui_source.h"
#include "qorai/components/qorai_wallet/browser/blockchain_registry.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_constants.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet_page/resources/grit/qorai_wallet_deposit_page_generated_map.h"
#include "qorai/components/qorai_wallet_page/resources/grit/qorai_wallet_fund_wallet_page_generated_map.h"
#include "qorai/components/qorai_wallet_page/resources/grit/qorai_wallet_page_generated_map.h"
#include "qorai/components/qorai_wallet_page/resources/grit/qorai_wallet_send_page_generated_map.h"
#include "qorai/components/qorai_wallet_page/resources/grit/qorai_wallet_swap_page_generated_map.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/webui/sanitized_image_source.h"
#include "components/grit/qorai_components_resources.h"
#include "components/grit/qorai_components_strings.h"
#include "content/public/browser/url_data_source.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_ui.h"
#include "content/public/common/url_constants.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/webui/webui_util.h"

AndroidWalletPageUI::AndroidWalletPageUI(content::WebUI* web_ui,
                                         const GURL& url)
    : ui::MojoWebUIController(web_ui,
                              true /* Needed for webui browser tests */) {
  CHECK(url.host() == kWalletPageHost);

  auto* profile = Profile::FromWebUI(web_ui);
  content::WebUIDataSource* source =
      content::WebUIDataSource::CreateAndAdd(profile, kWalletPageHost);
  web_ui->AddRequestableScheme(content::kChromeUIUntrustedScheme);

  for (const auto& str : qorai_wallet::kLocalizedStrings) {
    std::u16string l10n_str = l10n_util::GetStringUTF16(str.id);
    source->AddString(str.name, l10n_str);
  }

  // Add required resources.
  webui::SetupWebUIDataSource(source, base::span(kQoraiWalletPageGenerated),
                              IDR_WALLET_PAGE_HTML);

  source->AddBoolean("isMobile", true);
  source->AddString("qoraiWalletLedgerBridgeUrl", kUntrustedLedgerURL);
  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::FrameSrc,
      std::string("frame-src ") + kUntrustedTrezorURL + " " +
          kUntrustedLedgerURL + " " + kUntrustedNftURL + " " +
          kUntrustedLineChartURL + " " + kUntrustedMarketURL + ";");
  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::ImgSrc,
      base::JoinString({"img-src", "'self'", "chrome://resources",
                        "chrome://erc-token-images", "chrome://image",
                        base::StrCat({"data:", ";"})},
                       " "));
  source->AddString("qoraiWalletTrezorBridgeUrl", kUntrustedTrezorURL);
  source->AddString("qoraiWalletNftBridgeUrl", kUntrustedNftURL);
  source->AddString("qoraiWalletLineChartBridgeUrl", kUntrustedLineChartURL);
  source->AddString("qoraiWalletMarketUiBridgeUrl", kUntrustedMarketURL);
  source->AddBoolean(qorai_wallet::mojom::kP3ACountTestNetworksLoadTimeKey,
                     base::CommandLine::ForCurrentProcess()->HasSwitch(
                         qorai_wallet::mojom::kP3ACountTestNetworksSwitch));

  // Rewards UI features are not currently supported on Android.
  source->AddBoolean("rewardsFeatureEnabled", false);

  content::URLDataSource::Add(profile,
                              std::make_unique<SanitizedImageSource>(profile));
  qorai_wallet::AddBlockchainTokenImageSource(profile);
}

AndroidWalletPageUI::~AndroidWalletPageUI() = default;

void AndroidWalletPageUI::BindInterface(
    mojo::PendingReceiver<qorai_wallet::mojom::PageHandlerFactory> receiver) {
  page_factory_receiver_.reset();
  page_factory_receiver_.Bind(std::move(receiver));
}

WEB_UI_CONTROLLER_TYPE_IMPL(AndroidWalletPageUI)

void AndroidWalletPageUI::CreatePageHandler(
    mojo::PendingReceiver<qorai_wallet::mojom::PageHandler> page_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::WalletHandler> wallet_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::JsonRpcService>
        json_rpc_service_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::BitcoinWalletService>
        bitcoin_wallet_service_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::PolkadotWalletService>
        polkadot_wallet_service_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::ZCashWalletService>
        zcash_wallet_service_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::CardanoWalletService>
        cardano_wallet_service_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::SwapService>
        swap_service_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::AssetRatioService>
        asset_ratio_service_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::KeyringService>
        keyring_service_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::BlockchainRegistry>
        blockchain_registry_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::TxService> tx_service_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::EthTxManagerProxy>
        eth_tx_manager_proxy_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::SolanaTxManagerProxy>
        solana_tx_manager_proxy_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::FilTxManagerProxy>
        filecoin_tx_manager_proxy_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::BtcTxManagerProxy>
        bitcoin_tx_manager_proxy_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::QoraiWalletService>
        qorai_wallet_service_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::QoraiWalletP3A>
        qorai_wallet_p3a_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::IpfsService>
        ipfs_service_receiver,
    mojo::PendingReceiver<qorai_wallet::mojom::MeldIntegrationService>
        meld_integration_service) {
  auto* profile = Profile::FromWebUI(web_ui());
  CHECK(profile);
  page_handler_ = std::make_unique<AndroidWalletPageHandler>(
      std::move(page_receiver), profile, this);

  if (auto* wallet_service =
          qorai_wallet::QoraiWalletServiceFactory::GetServiceForContext(
              profile)) {
    wallet_handler_ = std::make_unique<qorai_wallet::WalletHandler>(
        std::move(wallet_receiver), wallet_service);
    wallet_service->Bind(std::move(qorai_wallet_service_receiver));
    wallet_service->Bind(std::move(json_rpc_service_receiver));
    wallet_service->Bind(std::move(bitcoin_wallet_service_receiver));
    wallet_service->Bind(std::move(polkadot_wallet_service_receiver));
    wallet_service->Bind(std::move(zcash_wallet_service_receiver));
    wallet_service->Bind(std::move(cardano_wallet_service_receiver));
    wallet_service->Bind(std::move(keyring_service_receiver));
    wallet_service->Bind(std::move(tx_service_receiver));
    wallet_service->Bind(std::move(eth_tx_manager_proxy_receiver));
    wallet_service->Bind(std::move(solana_tx_manager_proxy_receiver));
    wallet_service->Bind(std::move(filecoin_tx_manager_proxy_receiver));
    wallet_service->Bind(std::move(bitcoin_tx_manager_proxy_receiver));
    wallet_service->Bind(std::move(qorai_wallet_p3a_receiver));
  }

  qorai_wallet::SwapServiceFactory::BindForContext(
      profile, std::move(swap_service_receiver));
  qorai_wallet::AssetRatioServiceFactory::BindForContext(
      profile, std::move(asset_ratio_service_receiver));
  qorai_wallet::MeldIntegrationServiceFactory::BindForContext(
      profile, std::move(meld_integration_service));
  qorai_wallet::QoraiWalletIpfsServiceFactory::BindForContext(
      profile, std::move(ipfs_service_receiver));

  auto* blockchain_registry = qorai_wallet::BlockchainRegistry::GetInstance();
  if (blockchain_registry) {
    blockchain_registry->Bind(std::move(blockchain_registry_receiver));
  }
  qorai_wallet::WalletInteractionDetected(web_ui()->GetWebContents());
}
