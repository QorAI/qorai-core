// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import { QoraiWallet } from '../constants/types'
import { getLocale } from '../../common/locale'

export const AllAccountsOptionUniqueKey = 'all'

export const AllAccountsOption: QoraiWallet.AccountInfo = {
  address: AllAccountsOptionUniqueKey,
  accountId: {
    coin: 0,
    keyringId: QoraiWallet.KeyringId.kDefault,
    kind: QoraiWallet.AccountKind.kDerived,
    address: AllAccountsOptionUniqueKey,
    accountIndex: 0,
    uniqueKey: AllAccountsOptionUniqueKey,
  },
  name: getLocale('qoraiWalletAccountFilterAllAccounts'),
  hardware: undefined,
}

export const isAllAccountsOptionFilter = (selectedAccountFilter: string) => {
  return selectedAccountFilter === AllAccountsOptionUniqueKey
}
