/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { assertNotReached } from 'chrome://resources/js/assert.js'
import { QoraiWallet } from '../../constants/types'

import * as HWInterfaces from '../hardware/interfaces'
import EthereumLedgerBridgeKeyring from '../hardware/ledgerjs/eth_ledger_bridge_keyring'
import SolanaLedgerBridgeKeyring from '../hardware/ledgerjs/sol_ledger_bridge_keyring'
import TrezorBridgeKeyring from '../hardware/trezor/trezor_bridge_keyring'
import FilecoinLedgerBridgeKeyring from '../hardware/ledgerjs/fil_ledger_bridge_keyring'
import BitcoinLedgerBridgeKeyring from '../hardware/ledgerjs/btc_ledger_bridge_keyring'

// Lazy instances for keyrings
let ethereumHardwareKeyring: EthereumLedgerBridgeKeyring
let filecoinHardwareKeyring: FilecoinLedgerBridgeKeyring
let solanaHardwareKeyring: SolanaLedgerBridgeKeyring
let bitcoinHardwareKeyring: BitcoinLedgerBridgeKeyring
let trezorHardwareKeyring: TrezorBridgeKeyring

export function getHardwareKeyring(
  vendor: QoraiWallet.HardwareVendor,
  coin: QoraiWallet.CoinType,
  onAuthorized?: () => void,
):
  | EthereumLedgerBridgeKeyring
  | HWInterfaces.TrezorKeyring
  | FilecoinLedgerBridgeKeyring
  | SolanaLedgerBridgeKeyring
  | BitcoinLedgerBridgeKeyring {
  if (vendor === QoraiWallet.HardwareVendor.kLedger) {
    if (coin === QoraiWallet.CoinType.ETH) {
      return getLedgerEthereumHardwareKeyring(onAuthorized)
    } else if (coin === QoraiWallet.CoinType.FIL) {
      return getLedgerFilecoinHardwareKeyring(onAuthorized)
    } else if (coin === QoraiWallet.CoinType.SOL) {
      return getLedgerSolanaHardwareKeyring(onAuthorized)
    } else if (coin === QoraiWallet.CoinType.BTC) {
      return getLedgerBitcoinHardwareKeyring(onAuthorized)
    }
  } else if (vendor === QoraiWallet.HardwareVendor.kTrezor) {
    if (coin === QoraiWallet.CoinType.ETH) {
      return getTrezorHardwareKeyring()
    }
  }

  assertNotReached(`Unsupported coin ${coin} and vendor ${vendor}`)
}

export function getLedgerEthereumHardwareKeyring(
  onAuthorized?: () => void,
): EthereumLedgerBridgeKeyring {
  if (!ethereumHardwareKeyring) {
    ethereumHardwareKeyring = new EthereumLedgerBridgeKeyring(onAuthorized)
  }
  return ethereumHardwareKeyring
}

export function getLedgerFilecoinHardwareKeyring(
  onAuthorized?: () => void,
): FilecoinLedgerBridgeKeyring {
  if (!filecoinHardwareKeyring) {
    filecoinHardwareKeyring = new FilecoinLedgerBridgeKeyring(onAuthorized)
  }
  return filecoinHardwareKeyring
}

export function getLedgerSolanaHardwareKeyring(
  onAuthorized?: () => void,
): SolanaLedgerBridgeKeyring {
  if (!solanaHardwareKeyring) {
    solanaHardwareKeyring = new SolanaLedgerBridgeKeyring(onAuthorized)
  }
  return solanaHardwareKeyring
}

export function getLedgerBitcoinHardwareKeyring(
  onAuthorized?: () => void,
): BitcoinLedgerBridgeKeyring {
  if (!bitcoinHardwareKeyring) {
    bitcoinHardwareKeyring = new BitcoinLedgerBridgeKeyring(onAuthorized)
  }
  return bitcoinHardwareKeyring
}

export function getTrezorHardwareKeyring(): TrezorBridgeKeyring {
  if (!trezorHardwareKeyring) {
    trezorHardwareKeyring = new TrezorBridgeKeyring()
  }
  return trezorHardwareKeyring
}
