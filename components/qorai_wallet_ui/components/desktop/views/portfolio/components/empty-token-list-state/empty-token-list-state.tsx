// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import Button from '@qorai/qora/react/button'
import { useHistory } from 'react-router'

// Types
import { WalletRoutes } from '../../../../../../constants/types'

// Utils
import { getLocale } from '../../../../../../../common/locale'

// Styled Components
import {
  StyledWrapper,
  Title,
  Description,
  ButtonWrapper,
  EmptyStateIcon,
} from './empty-token-list-state.style'
import {
  Row,
  VerticalSpace,
  HorizontalSpace,
} from '../../../../../shared/style'

interface Props {
  onDepositOverride?: () => void
  onBuyOverride?: () => void
}

export const EmptyTokenListState = (props: Props) => {
  const { onDepositOverride, onBuyOverride } = props

  // routing
  const history = useHistory()

  // methods
  const onDeposit = React.useCallback(() => {
    if (onDepositOverride) {
      onDepositOverride()
      return
    }
    history.push(WalletRoutes.DepositFundsPageStart)
  }, [onDepositOverride, history])

  const onBuy = React.useCallback(() => {
    if (onBuyOverride) {
      onBuyOverride()
      return
    }
    history.push(WalletRoutes.FundWalletPageStart)
  }, [onBuyOverride, history])

  return (
    <StyledWrapper
      fullWidth={true}
      alignItems='center'
      justifyContent='center'
    >
      <EmptyStateIcon />
      <Title
        textSize='16px'
        isBold={true}
      >
        {getLocale('qoraiWalletNoAvailableAssets')}
      </Title>
      <Description
        textSize='14px'
        isBold={false}
      >
        {getLocale('qoraiWalletNoAvailableAssetsDescription')}
      </Description>
      <VerticalSpace space='24px' />
      <Row marginBottom={4}>
        <ButtonWrapper>
          <Button
            kind='outline'
            onClick={onBuy}
          >
            {getLocale('qoraiWalletBuyCryptoButton')}
          </Button>
        </ButtonWrapper>
        <HorizontalSpace space='12px' />
        <ButtonWrapper>
          <Button
            kind='outline'
            onClick={onDeposit}
          >
            {getLocale('qoraiWalletDepositCryptoButton')}
          </Button>
        </ButtonWrapper>
      </Row>
      <Description
        textSize='12px'
        isBold={false}
      >
        {getLocale('qoraiWalletWelcomeDividerText')}
      </Description>
      <Button
        kind='plain'
        onClick={() => history.push(WalletRoutes.AddAssetModal)}
      >
        {getLocale('qoraiWalletWatchlistAddCustomAsset')}
      </Button>
    </StyledWrapper>
  )
}

export default EmptyTokenListState
