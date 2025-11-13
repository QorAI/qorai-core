/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "qorai/browser/ui/webui/qorai_wallet/wallet_page_ui.h"

#include <string>
#include <utility>

#include "base/check.h"
#include "base/command_line.h"
#include "base/files/file_path.h"
#include "qorai/browser/qorai_ads/ads_service_factory.h"
#include "qorai/browser/qorai_rewards/rewards_service_factory.h"
#include "qorai/browser/qorai_rewards/rewards_util.h"
#include "qorai/browser/qorai_wallet/asset_ratio_service_factory.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_context_utils.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_ipfs_service_factory.h"
#include "qorai/browser/qorai_wallet/qorai_wallet_service_factory.h"
#include "qorai/browser/qorai_wallet/meld_integration_service_factory.h"
#include "qorai/browser/qorai_wallet/swap_service_factory.h"
#include "qorai/browser/ui/webui/qorai_rewards/rewards_page_handler.h"
#include "qorai/browser/ui/webui/qorai_wallet/wallet_common_ui.h"
#include "qorai/browser/ui/webui/navigation_bar_data_provider.h"
#include "qorai/components/qorai_wallet/browser/asset_ratio_service.h"
#include "qorai/components/qorai_wallet/browser/blockchain_registry.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_constants.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_ipfs_service.h"
#include "qorai/components/qorai_wallet/browser/qorai_wallet_service.h"
#include "qorai/components/qorai_wallet/browser/json_rpc_service.h"
#include "qorai/components/qorai_wallet/browser/keyring_service.h"
#include "qorai/components/qorai_wallet/browser/simulation_service.h"
#include "qorai/components/qorai_wallet/browser/swap_service.h"
#include "qorai/components/qorai_wallet/browser/tx_service.h"
#include "qorai/components/qorai_wallet/common/common_utils.h"
#include "qorai/components/qorai_wallet_page/resources/grit/qorai_wallet_page_generated_map.h"
#include "qorai/components/constants/webui_url_constants.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/webui/plural_string_handler.h"
#include "chrome/browser/ui/webui/sanitized_image_source.h"
#include "chrome/browser/ui/webui/theme_source.h"
#include "components/grit/qorai_components_resources.h"
#include "components/grit/qorai_components_strings.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_ui.h"
#include "content/public/browser/web_ui_data_source.h"
#include "content/public/common/url_constants.h"
#include "ui/base/accelerators/accelerator.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/webui/web_ui_util.h"
#include "ui/webui/webui_util.h"

WalletPageUI::WalletPageUI(content::WebUI* web_ui)
    : ui::MojoWebUIController(web_ui,
                              true /* Needed for webui browser tests */) {
  auto* profile = Profile::FromWebUI(web_ui);
  content::WebUIDataSource* source =
      content::WebUIDataSource::CreateAndAdd(profile, kWalletPageHost);
  web_ui->AddRequestableScheme(content::kChromeUIUntrustedScheme);
  for (const auto& str : qorai_wallet::kLocalizedStrings) {
    std::u16string l10n_str = l10n_util::GetStringUTF16(str.id);
    source->AddString(str.name, l10n_str);
  }
  auto plural_string_handler = std::make_unique<PluralStringHandler>();
  plural_string_handler->AddLocalizedString(
      "qoraiWalletExchangeNamePlusSteps",
      IDS_QORAI_WALLET_EXCHANGE_NAME_PLUS_STEPS);
  plural_string_handler->AddLocalizedString(
      "qoraiWalletPendingTransactions", IDS_QORAI_WALLET_PENDING_TRANSACTIONS);
  web_ui->AddMessageHandler(std::move(plural_string_handler));
  NavigationBarDataProvider::Initialize(source, profile);
  webui::SetupWebUIDataSource(source, base::span(kQoraiWalletPageGenerated),
                              IDR_WALLET_PAGE_HTML);
  source->AddString("qoraiWalletLedgerBridgeUrl", kUntrustedLedgerURL);
  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::ImgSrc,
      "img-src 'self' data: chrome://resources chrome://erc-token-images "
      "chrome://image;");
  source->OverrideContentSecurityPolicy(
      network::mojom::CSPDirectiveName::FrameSrc,
      std::string("frame-src ") + kUntrustedTrezorURL + " " +
          kUntrustedLedgerURL + " " + kUntrustedNftURL + " " +
          kUntrustedLineChartURL + " " + kUntrustedMarketURL + ";");
  source->AddString("qoraiWalletTrezorBridgeUrl", kUntrustedTrezorURL);
  source->AddString("qoraiWalletNftBridgeUrl", kUntrustedNftURL);
  source->AddString("qoraiWalletLineChartBridgeUrl", kUntrustedLineChartURL);
  source->AddString("qoraiWalletMarketUiBridgeUrl", kUntrustedMarketURL);
  source->AddBoolean("isMobile", false);
  source->AddBoolean(qorai_wallet::mojom::kP3ACountTestNetworksLoadTimeKey,
                     base::CommandLine::ForCurrentProcess()->HasSwitch(
                         qorai_wallet::mojom::kP3ACountTestNetworksSwitch));
  source->AddBoolean("rewardsFeatureEnabled",
                     qorai_rewards::IsSupportedForProfile(profile));
  content::URLDataSource::Add(profile,
                              std::make_unique<SanitizedImageSource>(profile));
  content::URLDataSource::Add(profile, std::make_unique<ThemeSource>(profile));
  qorai_wallet::AddBlockchainTokenImageSource(profile);
}

WalletPageUI::~WalletPageUI() = default;
WEB_UI_CONTROLLER_TYPE_IMPL(WalletPageUI)

void WalletPageUI::BindInterface(
    mojo::PendingReceiver<qorai_wallet::mojom::PageHandlerFactory> receiver) {
  page_factory_receiver_.reset();
  page_factory_receiver_.Bind(std::move(receiver));
}

void WalletPageUI::BindInterface(
    mojo::PendingReceiver<qorai_rewards::mojom::RewardsPageHandler> receiver) {
  auto* profile = Profile::FromWebUI(web_ui());
  CHECK(profile);

  rewards_handler_ = std::make_unique<qorai_rewards::RewardsPageHandler>(
      std::move(receiver), nullptr,
      qorai_rewards::RewardsServiceFactory::GetForProfile(profile),
      qorai_ads::AdsServiceFactory::GetForProfile(profile), nullptr,
      profile->GetPrefs());
}

void WalletPageUI::CreatePageHandler(
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

  page_handler_ =
      std::make_unique<WalletPageHandler>(std::move(page_receiver), profile);

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
}

WalletPageUIConfig::WalletPageUIConfig()
    : DefaultWebUIConfig(content::kChromeUIScheme, kWalletPageHost) {}

bool WalletPageUIConfig::IsWebUIEnabled(
    content::BrowserContext* browser_context) {
  return qorai_wallet::IsNativeWalletEnabled() &&
         qorai_wallet::IsAllowedForContext(browser_context);
}
