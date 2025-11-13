// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef QORAI_BROWSER_UI_WEBUI_QORAI_WALLET_ANDROID_ANDROID_WALLET_PAGE_UI_H_
#define QORAI_BROWSER_UI_WEBUI_QORAI_WALLET_ANDROID_ANDROID_WALLET_PAGE_UI_H_

#include <memory>
#include <string>

#include "qorai/browser/ui/webui/qorai_wallet/android/android_wallet_page_handler.h"
#include "qorai/components/qorai_wallet/browser/wallet_handler.h"
#include "qorai/components/qorai_wallet/common/qorai_wallet.mojom.h"
#include "content/public/browser/web_ui_controller.h"
#include "content/public/browser/web_ui_data_source.h"
#include "ui/webui/mojo_web_ui_controller.h"

class AndroidWalletPageUI : public ui::MojoWebUIController,
                            public qorai_wallet::mojom::PageHandlerFactory {
 public:
  explicit AndroidWalletPageUI(content::WebUI* web_ui, const GURL& url);
  AndroidWalletPageUI(const AndroidWalletPageUI&) = delete;
  AndroidWalletPageUI& operator=(const AndroidWalletPageUI&) = delete;
  ~AndroidWalletPageUI() override;

  // Instantiates the implementor of the mojom::PageHandlerFactory mojo
  // interface passing the pending receiver that will be internally bound.
  void BindInterface(
      mojo::PendingReceiver<qorai_wallet::mojom::PageHandlerFactory> receiver);
  WEB_UI_CONTROLLER_TYPE_DECL();

 private:
  // qorai_wallet::mojom::PageHandlerFactory:
  void CreatePageHandler(
      mojo::PendingReceiver<qorai_wallet::mojom::PageHandler> page_receiver,
      mojo::PendingReceiver<qorai_wallet::mojom::WalletHandler> wallet_receiver,
      mojo::PendingReceiver<qorai_wallet::mojom::JsonRpcService>
          json_rpc_service,
      mojo::PendingReceiver<qorai_wallet::mojom::BitcoinWalletService>
          bitcoin_wallet_service_receiver,
      mojo::PendingReceiver<qorai_wallet::mojom::PolkadotWalletService>
          polkadot_wallet_service_receiver,
      mojo::PendingReceiver<qorai_wallet::mojom::ZCashWalletService>
          zcash_wallet_service_receiver,
      mojo::PendingReceiver<qorai_wallet::mojom::CardanoWalletService>
          cardano_wallet_service_receiver,
      mojo::PendingReceiver<qorai_wallet::mojom::SwapService> swap_service,
      mojo::PendingReceiver<qorai_wallet::mojom::AssetRatioService>
          asset_ratio_service,
      mojo::PendingReceiver<qorai_wallet::mojom::KeyringService>
          keyring_service,
      mojo::PendingReceiver<qorai_wallet::mojom::BlockchainRegistry>
          blockchain_registry,
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
      mojo::PendingReceiver<qorai_wallet::mojom::QoraiWalletP3A>
          qorai_wallet_p3a,
      mojo::PendingReceiver<qorai_wallet::mojom::IpfsService>
          ipfs_service_receiver,
      mojo::PendingReceiver<qorai_wallet::mojom::MeldIntegrationService>
          meld_integration_service) override;

  std::unique_ptr<AndroidWalletPageHandler> page_handler_;
  std::unique_ptr<qorai_wallet::WalletHandler> wallet_handler_;

  mojo::Receiver<qorai_wallet::mojom::PageHandlerFactory>
      page_factory_receiver_{this};
};

#endif  // QORAI_BROWSER_UI_WEBUI_QORAI_WALLET_ANDROID_ANDROID_WALLET_PAGE_UI_H_
