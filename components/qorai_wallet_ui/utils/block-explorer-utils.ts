// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

// types
import { BlockExplorerUrlTypes, QoraiWallet } from '../constants/types'

// utils
import { getLocale } from '../../common/locale'
import Amount from './amount'

export const buildExplorerUrl = (
  network: Pick<QoraiWallet.NetworkInfo, 'chainId' | 'blockExplorerUrls'>,
  type: BlockExplorerUrlTypes,
  value?: string,
  id?: string,
) => {
  const explorerURL = network.blockExplorerUrls[0]

  const fallbackURL = `${explorerURL}/${value}`

  if (type === 'lifi') {
    return `https://scan.li.fi/tx/${value}`
  }

  if (type === 'nft') {
    return id
      ? `${explorerURL}/token/${value}?a=${new Amount(id).format()}`
      : fallbackURL
  }

  if (type === 'contract') {
    return `${explorerURL}/address/${value}/#code`
  }

  const isFileCoinNet =
    network.chainId === QoraiWallet.FILECOIN_TESTNET
    || network.chainId === QoraiWallet.FILECOIN_MAINNET

  const isFileCoinEvmNet =
    network.chainId === QoraiWallet.FILECOIN_ETHEREUM_MAINNET_CHAIN_ID
    || network.chainId === QoraiWallet.FILECOIN_ETHEREUM_TESTNET_CHAIN_ID

  const isSolanaMainNet = network.chainId === QoraiWallet.SOLANA_MAINNET

  const isSolanaDevOrTestNet =
    network.chainId === QoraiWallet.SOLANA_TESTNET
    || network.chainId === QoraiWallet.SOLANA_DEVNET

  const isZecNet =
    network.chainId === QoraiWallet.Z_CASH_MAINNET
    || network.chainId === QoraiWallet.Z_CASH_TESTNET

  const isCardanoNet =
    network.chainId === QoraiWallet.CARDANO_MAINNET
    || network.chainId === QoraiWallet.CARDANO_TESTNET

  if (isFileCoinNet) {
    return `${explorerURL}?cid=${value}`
  }

  if (isFileCoinEvmNet) {
    return `${explorerURL}/${value}`
  }

  if (isZecNet) {
    return `${explorerURL}/${value}`
  }

  if (isCardanoNet) {
    return `${explorerURL}/${type}/${value}`
  }

  if (isSolanaMainNet && type === 'token') {
    return `${explorerURL}/address/${value}`
  }

  if (isSolanaDevOrTestNet) {
    const explorerIndex = explorerURL.lastIndexOf('?')
    return `${explorerURL.substring(
      0,
      explorerIndex,
    )}/${type}/${value}${explorerURL.substring(explorerIndex)}`
  }

  if (network.chainId === QoraiWallet.BITCOIN_MAINNET) {
    if (type === 'tx') {
      return `${explorerURL}/transactions/btc/${value}`
    }
    if (type === 'address') {
      return `${explorerURL}/addresses/btc/${value}`
    }
    return `${explorerURL}/search?search=${value}`
  }

  return `${explorerURL}/${type}/${value}`
}

export const openBlockExplorerURL = ({
  id,
  network,
  type,
  value,
}: {
  id?: string | undefined
  network?: Pick<
    QoraiWallet.NetworkInfo,
    'chainId' | 'blockExplorerUrls'
  > | null
  type: BlockExplorerUrlTypes
  value?: string | undefined
}): (() => void) => {
  return () => {
    if (!network) {
      return
    }

    const explorerBaseURL = network.blockExplorerUrls[0]
    if (!explorerBaseURL || !value) {
      alert(getLocale('qoraiWalletTransactionExplorerMissing'))
      return
    }

    const url = buildExplorerUrl(network, type, value, id)

    if (!chrome.tabs) {
      window.open(url, '_blank', 'noreferrer')
    } else {
      chrome.tabs.create({ url: url }, () => {
        if (chrome.runtime.lastError) {
          console.error(
            'tabs.create failed: ' + chrome.runtime.lastError.message,
          )
        }
      })
    }
  }
}
