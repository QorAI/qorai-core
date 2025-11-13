// Copyright (c) 2021 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import WalletApiProxy from '../common/wallet_api_proxy'
import { QoraiWallet } from '../constants/types'

let walletPageApiProxyInstance: WalletPageApiProxy

export class WalletPageApiProxy extends WalletApiProxy {
  pageHandler = new QoraiWallet.PageHandlerRemote()
  constructor() {
    super()

    const factory = QoraiWallet?.PageHandlerFactory?.getRemote?.()
    factory?.createPageHandler?.(
      this.pageHandler.$.bindNewPipeAndPassReceiver(),
      this.walletHandler.$.bindNewPipeAndPassReceiver(),
      this.jsonRpcService.$.bindNewPipeAndPassReceiver(),
      this.bitcoinWalletService.$.bindNewPipeAndPassReceiver(),
      this.polkadotWalletService.$.bindNewPipeAndPassReceiver(),
      this.zcashWalletService.$.bindNewPipeAndPassReceiver(),
      this.cardanoWalletService.$.bindNewPipeAndPassReceiver(),
      this.swapService.$.bindNewPipeAndPassReceiver(),
      this.assetRatioService.$.bindNewPipeAndPassReceiver(),
      this.keyringService.$.bindNewPipeAndPassReceiver(),
      this.blockchainRegistry.$.bindNewPipeAndPassReceiver(),
      this.txService.$.bindNewPipeAndPassReceiver(),
      this.ethTxManagerProxy.$.bindNewPipeAndPassReceiver(),
      this.solanaTxManagerProxy.$.bindNewPipeAndPassReceiver(),
      this.filTxManagerProxy.$.bindNewPipeAndPassReceiver(),
      this.btcTxManagerProxy.$.bindNewPipeAndPassReceiver(),
      this.qoraiWalletService.$.bindNewPipeAndPassReceiver(),
      this.qoraiWalletP3A.$.bindNewPipeAndPassReceiver(),
      this.qoraiWalletIpfsService.$.bindNewPipeAndPassReceiver(),
      this.meldIntegrationService.$.bindNewPipeAndPassReceiver(),
    )
  }
}

export default function getWalletPageApiProxy() {
  if (!walletPageApiProxyInstance) {
    walletPageApiProxyInstance = new WalletPageApiProxy()
  }
  return walletPageApiProxyInstance
}
