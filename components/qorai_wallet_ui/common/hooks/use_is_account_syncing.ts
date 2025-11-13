// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { skipToken } from '@reduxjs/toolkit/query/react'
import getAPIProxy from '../async/bridge'

// Types
import { QoraiWallet } from '../../constants/types'

// Selectors
import { useSafeWalletSelector } from './use-safe-selector'
import { WalletSelectors } from '../selectors'

// Utils
import { isComponentInStorybook } from '../../utils/string-utils'

// Hooks
import {
  useGetIsSyncInProgressQuery,
  useClearChainTipStatusCacheMutation,
  useClearZCashBalanceCacheMutation,
} from '../slices/api.slice'

const isStorybook = isComponentInStorybook()

export const useIsAccountSyncing = (accountId?: QoraiWallet.AccountId) => {
  // State
  const [syncingId, setSyncingId] = React.useState<string | undefined>()
  const [clearChainTipStatusCache] = useClearChainTipStatusCacheMutation()
  const [clearZCashBalanceCache] = useClearZCashBalanceCacheMutation()

  // Selectors
  const isZCashShieldedTransactionsEnabled = useSafeWalletSelector(
    WalletSelectors.isZCashShieldedTransactionsEnabled,
  )

  // Queries
  const { data: isSyncAlreadyInProgress } = useGetIsSyncInProgressQuery(
    isZCashShieldedTransactionsEnabled
      && !syncingId
      && accountId
      && accountId.coin === QoraiWallet.CoinType.ZEC
      ? accountId
      : skipToken,
  )

  // Effects
  React.useEffect(() => {
    // Unable to mock mojom for storybook
    if (isStorybook) {
      return
    }
    const zcashWalletServiceObserver =
      new QoraiWallet.ZCashWalletServiceObserverReceiver({
        onSyncStart: (id: QoraiWallet.AccountId) => {
          if (accountId && accountId.uniqueKey === id.uniqueKey) {
            setSyncingId(id.uniqueKey)
          }
        },
        onSyncStop: (id: QoraiWallet.AccountId) => {
          clearChainTipStatusCache()
          clearZCashBalanceCache()
          if (accountId && accountId.uniqueKey === id.uniqueKey) {
            setSyncingId('')
          }
        },
        onSyncStatusUpdate: () => {},
        onSyncError: () => {},
      })

    getAPIProxy().zcashWalletService.addObserver(
      zcashWalletServiceObserver.$.bindNewPipeAndPassRemote(),
    )

    return () => zcashWalletServiceObserver.$.close()
  }, [accountId, clearChainTipStatusCache, clearZCashBalanceCache])

  return syncingId === undefined
    ? isSyncAlreadyInProgress
    : accountId && syncingId === accountId.uniqueKey
}

export default useIsAccountSyncing
