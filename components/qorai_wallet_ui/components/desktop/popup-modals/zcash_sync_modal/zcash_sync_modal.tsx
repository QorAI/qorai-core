// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import Alert from '@qorai/qora/react/alert'
import Button from '@qorai/qora/react/button'
import Icon from '@qorai/qora/react/icon'
import getAPIProxy from '../../../../common/async/bridge'

// Hooks
import {
  useStartShieldSyncMutation,
  useStopShieldSyncMutation,
} from '../../../../common/slices/api.slice'

// Utils
import { openWalletRouteTab } from '../../../../utils/routes-utils'
import { getLocale } from '../../../../../common/locale'

// Types
import { QoraiWallet, WalletRoutes } from '../../../../constants/types'

// Components
import PopupModal from '..'

// Styled Components
import { ProgressRing } from './zcash_sync_modal.style'
import { Text, Column, Row } from '../../../shared/style'

const blocksPerRange = 1024

interface Props {
  account: QoraiWallet.AccountInfo
  onClose: () => void
}

export const ZCashSyncModal = (props: Props) => {
  const { account, onClose } = props

  // Mutations
  const [startShieldSync] = useStartShieldSyncMutation()
  const [stopShieldSync] = useStopShieldSyncMutation()

  // State
  const [syncStatus, setSyncStatus] = React.useState<
    'started' | 'stopped' | undefined
  >(undefined)
  const [syncError, setSyncError] = React.useState<string>('')
  const [startBlock, setStartBlock] = React.useState<number>(0)
  const [endBlock, setEndBlock] = React.useState<number>(0)
  const [scannedRanges, setScannedRanges] = React.useState<number>(0)
  const [totalRanges, setTotalRanges] = React.useState<number>(0)

  // Methods
  const onStartShieldSync = React.useCallback(async () => {
    await startShieldSync(account.accountId)
  }, [startShieldSync, account])

  const onStopShieldSync = React.useCallback(async () => {
    await stopShieldSync(account.accountId)
  }, [stopShieldSync, account])

  // effects
  React.useEffect(() => {
    const zcashWalletServiceObserver =
      new QoraiWallet.ZCashWalletServiceObserverReceiver({
        onSyncStart: (accountId: QoraiWallet.AccountId) => {
          if (account.accountId.uniqueKey === accountId.uniqueKey) {
            setSyncStatus('started')
          }
        },
        onSyncStop: (accountId: QoraiWallet.AccountId) => {
          if (account.accountId.uniqueKey === accountId.uniqueKey) {
            setSyncStatus('stopped')
          }
        },
        onSyncStatusUpdate: (
          accountId: QoraiWallet.AccountId,
          status: QoraiWallet.ZCashShieldSyncStatus,
        ) => {
          if (account.accountId.uniqueKey === accountId.uniqueKey) {
            setSyncStatus('started')
            setStartBlock(Number(status.startBlock))
            setEndBlock(Number(status.endBlock))
            setScannedRanges(Number(status.scannedRanges))
            setTotalRanges(Number(status.totalRanges))
          }
        },
        onSyncError: (accountId: QoraiWallet.AccountId, error: string) => {
          if (account.accountId.uniqueKey === accountId.uniqueKey) {
            setSyncError(error)
          }
        },
      })

    getAPIProxy().zcashWalletService.addObserver(
      zcashWalletServiceObserver.$.bindNewPipeAndPassRemote(),
    )

    return () => zcashWalletServiceObserver.$.close()
  }, [account])

  // Computed
  const percent =
    scannedRanges === 0 && totalRanges === 0
      ? 0
      : (scannedRanges / totalRanges) * 100
  const calculatedBlock =
    scannedRanges === 0
      ? startBlock
      : scannedRanges === totalRanges
        ? endBlock
        : scannedRanges * blocksPerRange + startBlock
  const syncComplete = syncStatus === 'stopped' && scannedRanges === totalRanges

  return (
    <PopupModal
      onClose={onClose}
      title={getLocale('qoraiWalletSyncAccountName').replace(
        '$1',
        account.name,
      )}
      width='600px'
    >
      <Column
        padding='40px'
        width='100%'
        justifyContent='flex-start'
      >
        <ProgressRing
          mode={syncStatus === undefined ? 'indeterminate' : 'determinate'}
          progress={syncStatus === undefined ? 0.25 : percent * 0.01}
        >
          {syncStatus !== undefined && (
            <Text
              textSize='22px'
              textColor='primary'
              isBold={true}
            >
              {Math.trunc(percent)}%
            </Text>
          )}
        </ProgressRing>
        <Column
          gap='24px'
          width='100%'
        >
          {syncStatus === undefined ? (
            <Text
              textSize='14px'
              textColor='primary'
              isBold={false}
            >
              {getLocale('qoraiWalletInitializing')}
            </Text>
          ) : (
            <>
              <Column gap='8px'>
                <Text
                  textSize='14px'
                  textColor='primary'
                  isBold={false}
                >
                  {getLocale('qoraiWalletProcessingBlock')}
                </Text>
                <Text
                  textSize='16px'
                  textColor='primary'
                  isBold={true}
                >
                  {getLocale('qoraiWalletBlocksLeft').replace(
                    '$1',
                    (endBlock - calculatedBlock).toLocaleString(),
                  )}
                </Text>
                <Text
                  textSize='12px'
                  textColor='tertiary'
                  isBold={false}
                >
                  {getLocale('qoraiWalletBlocksOfBlocks')
                    .replace('$1', calculatedBlock.toLocaleString())
                    .replace('$2', endBlock.toLocaleString())}
                </Text>
              </Column>
              <Column gap='8px'>
                <Text
                  textSize='14px'
                  textColor='primary'
                  isBold={false}
                >
                  {getLocale('qoraiWalletRanges')}
                </Text>
                <Text
                  textSize='16px'
                  textColor='primary'
                  isBold={true}
                >
                  {getLocale('qoraiWalletBlocksOfBlocks')
                    .replace('$1', scannedRanges.toLocaleString())
                    .replace('$2', totalRanges.toLocaleString())}
                </Text>
              </Column>
              <Button
                onClick={
                  syncComplete
                    ? onClose
                    : syncStatus === 'stopped'
                      ? onStartShieldSync
                      : onStopShieldSync
                }
                kind={syncComplete ? 'filled' : 'outline'}
              >
                {!syncComplete && (
                  <Icon
                    name={
                      syncStatus === 'stopped' ? 'play-filled' : 'pause-filled'
                    }
                    slot='icon-before'
                  />
                )}
                {syncComplete
                  ? getLocale('qoraiWalletButtonClose')
                  : syncStatus === 'stopped'
                    ? getLocale('qoraiWalletButtonContinue')
                    : getLocale('qoraiWalletPause')}
              </Button>
            </>
          )}
          {syncComplete && !syncError && (
            <Alert type='success'>
              {getLocale('qoraiWalletSyncCompleteMessage')}
            </Alert>
          )}
          {!syncComplete && !syncError && (
            <Alert type='warning'>
              {getLocale('qoraiWalletSyncStartedMessage')}
            </Alert>
          )}
          {syncError && <Alert type='error'>{syncError}</Alert>}
          {!syncComplete && (
            <Row justifyContent='center'>
              <div>
                <Button
                  onClick={() =>
                    openWalletRouteTab(WalletRoutes.PortfolioAssets)
                  }
                >
                  <Icon
                    name='launch'
                    slot='icon-before'
                  />
                  {getLocale('qoraiWalletContinueUsingWallet')}
                </Button>
              </div>
            </Row>
          )}
        </Column>
      </Column>
    </PopupModal>
  )
}
