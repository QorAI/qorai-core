// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { render, screen } from '@testing-library/react'

// Components
import { NetworkInfo } from './network_info'

// Mocks
import { mockBNBChainNetwork } from '../../../stories/mock-data/mock-networks'
import QoraiCoreThemeProvider from '../../../../common/QoraiCoreThemeProvider'

describe('NetworkInfo', () => {
  it('should render network information correctly', () => {
    const { container } = render(
      <QoraiCoreThemeProvider>
        <NetworkInfo network={mockBNBChainNetwork} />
      </QoraiCoreThemeProvider>,
    )

    // Check if the component renders
    expect(container).toBeInTheDocument()

    // Check if all network information sections are displayed
    expect(
      screen.getByText('qoraiWalletAllowAddNetworkName:'),
    ).toBeInTheDocument()
    expect(
      screen.getByText('qoraiWalletAllowAddNetworkUrl:'),
    ).toBeInTheDocument()
    expect(screen.getByText('qoraiWalletChainId:')).toBeInTheDocument()
    expect(
      screen.getByText('qoraiWalletAllowAddNetworkCurrencySymbol:'),
    ).toBeInTheDocument()
    expect(
      screen.getByText('qoraiWalletWatchListTokenDecimals:'),
    ).toBeInTheDocument()
    expect(
      screen.getByText('qoraiWalletAllowAddNetworkExplorer:'),
    ).toBeInTheDocument()

    // Check if network values are displayed
    expect(screen.getByText(mockBNBChainNetwork.chainName)).toBeInTheDocument()
    expect(
      screen.getByText(mockBNBChainNetwork.rpcEndpoints[0].url),
    ).toBeInTheDocument()
    expect(screen.getByText(mockBNBChainNetwork.chainId)).toBeInTheDocument()
    expect(screen.getByText(mockBNBChainNetwork.symbol)).toBeInTheDocument()
    expect(
      screen.getByText(mockBNBChainNetwork.decimals.toString()),
    ).toBeInTheDocument()
    expect(
      screen.getByText(mockBNBChainNetwork.blockExplorerUrls[0]),
    ).toBeInTheDocument()
  })
})
