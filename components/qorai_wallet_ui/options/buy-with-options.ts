/* Copyright (c) 2021 The Qorai Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { getLocale } from '$web-common/locale'
import { QoraiWallet, BuyOption } from '../constants/types'

import RampIcon from '../assets/svg-icons/ramp-icon.svg'
import TransakIcon from '../assets/svg-icons/transak-logo.svg'
import StripeIcon from '../assets/svg-icons/stripe-logo.svg'
import CoinbaseIcon from '../assets/svg-icons/coinbase-logo.svg'
import { isStripeSupported } from '../utils/asset-utils'

function getBuyOptions(): BuyOption[] {
  const buyOptions = [
    {
      id: QoraiWallet.OnRampProvider.kRamp,
      actionText: getLocale('qoraiWalletBuyWithRamp'),
      icon: RampIcon,
      name: getLocale('qoraiWalletBuyRampNetworkName'),
      description: getLocale('qoraiWalletBuyRampDescription'),
    },
    {
      id: QoraiWallet.OnRampProvider.kTransak,
      actionText: getLocale('qoraiWalletBuyWithTransak'),
      icon: TransakIcon,
      name: getLocale('qoraiWalletBuyTransakName'),
      description: getLocale('qoraiWalletBuyTransakDescription'),
    },
    {
      id: QoraiWallet.OnRampProvider.kCoinbase,
      actionText: getLocale('qoraiWalletBuyWithCoinbase'),
      icon: CoinbaseIcon,
      name: getLocale('qoraiWalletBuyCoinbaseName'),
      description: getLocale('qoraiWalletBuyCoinbaseDescription'),
    },
  ]

  if (isStripeSupported()) {
    buyOptions.push({
      id: QoraiWallet.OnRampProvider.kStripe,
      actionText: getLocale('qoraiWalletBuyWithStripe'),
      icon: StripeIcon,
      name: getLocale('qoraiWalletBuyStripeName'),
      description: getLocale('qoraiWalletBuyStripeDescription'),
    })
  }

  return buyOptions
}

export const BuyOptions = getBuyOptions()
