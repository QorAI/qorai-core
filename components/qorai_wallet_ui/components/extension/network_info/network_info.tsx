// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

// Types
import { QoraiWallet } from '../../../constants/types'

// Utils
import { getLocale } from '../../../../common/locale'

// Styled Components
import {
  StyledWrapper,
  SectionLabel,
  SectionDetails,
} from './network_info.style'

// Shared Styles
import { Column } from '../../shared/style'

interface Props {
  network: QoraiWallet.NetworkInfo
}

export const NetworkInfo = (props: Props) => {
  const { network } = props

  return (
    <StyledWrapper
      alignItems='flex-start'
      justifyContent='flex-start'
      padding='16px'
      gap='16px'
      width='100%'
    >
      <Column
        alignItems='flex-start'
        justifyContent='flex-start'
      >
        <SectionLabel textColor='tertiary'>
          {getLocale('qoraiWalletAllowAddNetworkName')}:
        </SectionLabel>
        <SectionDetails textColor='primary'>{network.chainName}</SectionDetails>
      </Column>
      <Column
        alignItems='flex-start'
        justifyContent='flex-start'
      >
        <SectionLabel textColor='tertiary'>
          {getLocale('qoraiWalletAllowAddNetworkUrl')}:
        </SectionLabel>
        <SectionDetails textColor='primary'>
          {network.rpcEndpoints[0].url}
        </SectionDetails>
      </Column>
      <Column
        alignItems='flex-start'
        justifyContent='flex-start'
      >
        <SectionLabel textColor='tertiary'>
          {getLocale('qoraiWalletChainId')}:
        </SectionLabel>
        <SectionDetails textColor='primary'>{network.chainId}</SectionDetails>
      </Column>
      <Column
        alignItems='flex-start'
        justifyContent='flex-start'
      >
        <SectionLabel textColor='tertiary'>
          {getLocale('qoraiWalletAllowAddNetworkCurrencySymbol')}:
        </SectionLabel>
        <SectionDetails textColor='primary'>{network.symbol}</SectionDetails>
      </Column>
      <Column
        alignItems='flex-start'
        justifyContent='flex-start'
      >
        <SectionLabel textColor='tertiary'>
          {getLocale('qoraiWalletWatchListTokenDecimals')}:
        </SectionLabel>
        <SectionDetails textColor='primary'>{network.decimals}</SectionDetails>
      </Column>
      <Column
        alignItems='flex-start'
        justifyContent='flex-start'
      >
        <SectionLabel textColor='tertiary'>
          {getLocale('qoraiWalletAllowAddNetworkExplorer')}:
        </SectionLabel>
        <SectionDetails textColor='primary'>
          {network.blockExplorerUrls[0]}
        </SectionDetails>
      </Column>
    </StyledWrapper>
  )
}
