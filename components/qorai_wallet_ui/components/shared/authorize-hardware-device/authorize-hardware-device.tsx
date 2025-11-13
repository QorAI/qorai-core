/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { assertNotReached } from 'chrome://resources/js/assert.js'
import * as React from 'react'
import { StyledIFrame } from './style'
import { LEDGER_BRIDGE_URL } from '../../../common/hardware/ledgerjs/ledger-messages'
import { QoraiWallet } from '../../../constants/types'
import { BridgeTypes } from '../../../common/hardware/untrusted_shared_types'

export interface Props {
  coinType: QoraiWallet.CoinType
}

const bridgeTypeFromCoin = (coinType: QoraiWallet.CoinType) => {
  switch (coinType) {
    case QoraiWallet.CoinType.BTC:
      return BridgeTypes.BtcLedger
    case QoraiWallet.CoinType.ETH:
      return BridgeTypes.EthLedger
    case QoraiWallet.CoinType.SOL:
      return BridgeTypes.SolLedger
    case QoraiWallet.CoinType.FIL:
      return BridgeTypes.FilLedger
  }
  assertNotReached(`Unknown coin ${coinType}`)
}

export const AuthorizeHardwareDeviceIFrame = (props: Props) => {
  const src =
    LEDGER_BRIDGE_URL
    + `?targetUrl=${encodeURIComponent(window.origin)}`
    + `&bridgeType=${encodeURIComponent(bridgeTypeFromCoin(props.coinType))}`
  return (
    <StyledIFrame
      src={src}
      allow='hid'
      frameBorder='0'
      sandbox='allow-scripts allow-same-origin'
    />
  )
}

export default AuthorizeHardwareDeviceIFrame
