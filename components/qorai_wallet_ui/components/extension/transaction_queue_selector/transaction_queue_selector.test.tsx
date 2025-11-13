// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { render } from '@testing-library/react'

// Utils
import {
  // eslint-disable-next-line import/no-named-default
  default as QoraiCoreThemeProvider,
} from '../../../../common/QoraiCoreThemeProvider'

// Components
import { TransactionQueueSelector } from './transaction_queue_selector'

describe('AdvancedTransactionSettings', () => {
  it('should render the component', () => {
    const queueNextTransaction = jest.fn()
    const queuePreviousTransaction = jest.fn()
    const rejectAllTransactions = jest.fn()

    const { container } = render(
      <QoraiCoreThemeProvider>
        <TransactionQueueSelector
          transactionsQueueLength={5}
          queueNextTransaction={queueNextTransaction}
          queuePreviousTransaction={queuePreviousTransaction}
          rejectAllTransactions={rejectAllTransactions}
        />
      </QoraiCoreThemeProvider>,
    )

    // Check button
    const button = container.querySelector('qora-button')
    expect(button).toBeInTheDocument()
    expect(button).toHaveTextContent('qoraiWalletPendingTransactionsNumber')

    // Check menu items
    const menuItems = container.querySelectorAll('qora-menu-item')
    expect(menuItems).toHaveLength(3)
    expect(menuItems[0]).toHaveTextContent('qoraiWalletNextTransaction')
    expect(menuItems[1]).toHaveTextContent('qoraiWalletPreviousTransaction')
    expect(menuItems[2]).toHaveTextContent('qoraiWalletRejectTransactions')

    // Check Next transaction button
    const nextTransactionButton = menuItems[0] as HTMLElement
    nextTransactionButton.click()
    expect(queueNextTransaction).toHaveBeenCalled()

    // Check Previous transaction button
    const previousTransactionButton = menuItems[1] as HTMLElement
    previousTransactionButton.click()
    expect(queuePreviousTransaction).toHaveBeenCalled()

    // Check Reject transactions button
    const rejectTransactionsButton = menuItems[2] as HTMLElement
    rejectTransactionsButton.click()
    expect(rejectAllTransactions).toHaveBeenCalled()
  })
})
