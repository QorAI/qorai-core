// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { render, act, waitFor } from '@testing-library/react'

// Utils
import {
  // eslint-disable-next-line import/no-named-default
  default as QoraiCoreThemeProvider,
} from '../../../../../../common/QoraiCoreThemeProvider'
import { createMockStore } from '../../../../../utils/test-utils'

// Components
import { ShieldAccountAlert } from './shield_account_alert'

// Mocks
import { mockZecAccount } from '../../../../../common/constants/mocks'
import { Provider } from 'react-redux'

describe('ShieldAccountAlert', () => {
  it('should render', async () => {
    const store = createMockStore({})
    const { container } = render(
      <Provider store={store}>
        <QoraiCoreThemeProvider>
          <ShieldAccountAlert account={mockZecAccount} />
        </QoraiCoreThemeProvider>
      </Provider>,
    )

    // Check if the shield account alert is rendered
    expect(container).toBeInTheDocument()
    expect(container).toHaveTextContent('qoraiWalletShieldAccount')
    expect(container).toHaveTextContent(
      'qoraiWalletShieldAccountAlertDescription',
    )

    // Check if the shield account alert button is rendered
    const shieldAccountAlertButton: any = document.querySelector('qora-button')
    expect(shieldAccountAlertButton).toBeInTheDocument()
    expect(shieldAccountAlertButton?.textContent).toBe(
      'qoraiWalletShieldAccount',
    )

    // Check if the shield account alert button is clickable and opens the modal
    act(() => {
      shieldAccountAlertButton?.shadowRoot?.querySelector('button').click()
    })

    await waitFor(() => {
      expect(container).toHaveTextContent('qoraiWalletSwitchToShieldedAccount')
      expect(container).toHaveTextContent(
        'qoraiWalletAccountNotShieldedDescription',
      )
      expect(container).toHaveTextContent(
        'qoraiWalletAccountShieldedDescription',
      )
      expect(container).toHaveTextContent(
        'qoraiWalletAdvancedTransactionSettings',
      )
      expect(container).toHaveTextContent('qoraiWalletShieldAccount')
    })
  })
})
