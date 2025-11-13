// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import Icon from '@qorai/qora/react/icon'

// Utils
import { getLocale } from '../../../../common/locale'

// Styled components
import { Button, ButtonMenu } from './transaction_queue_selector.style'
import { Row } from '../../shared/style'

interface Props {
  transactionsQueueLength: number
  queueNextTransaction: () => void
  queuePreviousTransaction: () => void
  rejectAllTransactions: () => void
}

export function TransactionQueueSelector(props: Props) {
  const {
    transactionsQueueLength,
    queueNextTransaction,
    queuePreviousTransaction,
    rejectAllTransactions,
  } = props
  const [showMenu, setShowMenu] = React.useState(false)

  if (transactionsQueueLength <= 1) {
    return null
  }

  return (
    <ButtonMenu
      isOpen={showMenu}
      onChange={({ isOpen }) => setShowMenu(isOpen)}
      onClose={() => setShowMenu(false)}
      placement='bottom-end'
    >
      <Button
        size='tiny'
        kind='plain'
        slot='anchor-content'
      >
        {getLocale('qoraiWalletPendingTransactionsNumber').replace(
          '$1',
          transactionsQueueLength.toString(),
        )}
        <Icon
          slot='icon-after'
          name='more-vertical'
        />
      </Button>
      <qora-menu-item onClick={queueNextTransaction}>
        <Icon name='carat-right' />
        {getLocale('qoraiWalletNextTransaction')}
      </qora-menu-item>
      <qora-menu-item onClick={queuePreviousTransaction}>
        <Row
          justifyContent='flex-start'
          gap='8px'
        >
          <Icon name='carat-left' />
          {getLocale('qoraiWalletPreviousTransaction')}
        </Row>
      </qora-menu-item>
      <qora-menu-item onClick={rejectAllTransactions}>
        <Row
          justifyContent='flex-start'
          gap='8px'
        >
          <Icon name='close-circle' />
          {getLocale('qoraiWalletRejectTransactions').replace(
            '$1',
            transactionsQueueLength.toString(),
          )}
        </Row>
      </qora-menu-item>
    </ButtonMenu>
  )
}

export default TransactionQueueSelector
