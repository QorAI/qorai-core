// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import { TopTabNavObjectType } from '../constants/types'
import { getLocale } from '$web-common/locale'

export const TopNavOptions = (): TopTabNavObjectType[] => [
  {
    id: 'portfolio',
    name: getLocale('qoraiWalletTopNavPortfolio'),
  },
  {
    id: 'nfts',
    name: getLocale('qoraiWalletTopNavNFTS'),
  },
  {
    id: 'activity', // Transactions
    name: getLocale('qoraiWalletActivity'),
  },
  {
    id: 'accounts',
    name: getLocale('qoraiWalletTopNavAccounts'),
  },
  {
    id: 'market',
    name: getLocale('qoraiWalletTopNavMarket'),
  },
  // Temp commented out for MVP
  // {
  //   id: 'apps',
  //   name: getLocale('qoraiWalletTopTabApps')
  // }
]

export const TOP_NAV_OPTIONS = TopNavOptions()
