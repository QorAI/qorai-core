// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import { QoraiWallet } from '../constants/types'

export class WalletApiProxy {
  walletHandler = new QoraiWallet.WalletHandlerRemote()
  jsonRpcService = new QoraiWallet.JsonRpcServiceRemote()
  bitcoinWalletService = new QoraiWallet.BitcoinWalletServiceRemote()
  polkadotWalletService = new QoraiWallet.PolkadotWalletServiceRemote()
  zcashWalletService = new QoraiWallet.ZCashWalletServiceRemote()
  cardanoWalletService = new QoraiWallet.CardanoWalletServiceRemote()
  swapService = new QoraiWallet.SwapServiceRemote()
  simulationService = new QoraiWallet.SimulationServiceRemote()
  assetRatioService = new QoraiWallet.AssetRatioServiceRemote()
  meldIntegrationService = new QoraiWallet.MeldIntegrationServiceRemote()
  keyringService = new QoraiWallet.KeyringServiceRemote()
  blockchainRegistry = new QoraiWallet.BlockchainRegistryRemote()
  txService = new QoraiWallet.TxServiceRemote()
  ethTxManagerProxy = new QoraiWallet.EthTxManagerProxyRemote()
  solanaTxManagerProxy = new QoraiWallet.SolanaTxManagerProxyRemote()
  filTxManagerProxy = new QoraiWallet.FilTxManagerProxyRemote()
  btcTxManagerProxy = new QoraiWallet.BtcTxManagerProxyRemote()
  qoraiWalletService = new QoraiWallet.QoraiWalletServiceRemote()
  qoraiWalletP3A = new QoraiWallet.QoraiWalletP3ARemote()
  qoraiWalletIpfsService = new QoraiWallet.IpfsServiceRemote()

  addJsonRpcServiceObserver(
    observer: QoraiWallet.JsonRpcServiceObserverReceiver,
  ) {
    this.jsonRpcService.addObserver(observer.$.bindNewPipeAndPassRemote())
  }

  addKeyringServiceObserver(
    observer: QoraiWallet.KeyringServiceObserverReceiver,
  ) {
    this.keyringService.addObserver(observer.$.bindNewPipeAndPassRemote())
  }

  addTxServiceObserver(observer: QoraiWallet.TxServiceObserverReceiver) {
    this.txService.addObserver(observer.$.bindNewPipeAndPassRemote())
  }

  addQoraiWalletServiceObserver(
    observer: QoraiWallet.QoraiWalletServiceObserverReceiver,
  ) {
    this.qoraiWalletService.addObserver(observer.$.bindNewPipeAndPassRemote())
  }

  addQoraiWalletServiceTokenObserver(
    observer: QoraiWallet.QoraiWalletServiceTokenObserverReceiver,
  ) {
    this.qoraiWalletService.addTokenObserver(
      observer.$.bindNewPipeAndPassRemote(),
    )
  }
}

export default WalletApiProxy
