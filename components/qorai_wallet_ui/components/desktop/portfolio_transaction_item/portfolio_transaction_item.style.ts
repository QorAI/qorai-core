// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Icon from '@qorai/qora/react/icon'
import ProgressRing from '@qorai/qora/react/progressRing'

// Types
import { QoraiWallet } from '../../../constants/types'

// Shared Styles
import {
  Text,
  AssetIconFactory,
  AssetIconProps,
  Column,
} from '../../shared/style'

export const PortfolioTransactionItemWrapper = styled.div<{
  isFocused?: boolean
}>`
  display: flex;
  align-items: center;
  justify-content: space-between;
  flex-direction: row;
  width: 100%;
  position: relative;
  transition: background-color 300ms ease-out;
  background-color: ${(p) =>
    p.isFocused ? `${qora.color.page.background}` : 'none'};
  padding: 12px 16px;
  border-radius: 12px;
  border: 1px solid ${qora.color.divider.subtle};
  cursor: pointer;
  &:hover {
    background-color: ${qora.color.page.background};
  }
`

export const TransactionTypeIcon = styled(Icon)`
  --qora-icon-size: 12px;
  color: ${qora.color.icon.default};
  margin-right: 4px;
`

export const DateText = styled(Text)`
  line-height: 18px;
  color: ${qora.color.text.tertiary};
  margin-right: 8px;
`

export const TransactionTypeText = styled(Text)`
  line-height: 18px;
  color: ${qora.color.text.tertiary};
  text-transform: capitalize;
  margin-right: 4px;
`

export const IntentAddressText = styled(Text)`
  line-height: 18px;
  color: ${qora.color.text.tertiary};
`

const assetIconProps = {
  width: '32px',
  height: 'auto',
}
export const AssetIcon = AssetIconFactory<AssetIconProps>(assetIconProps)

const swapIconProps = {
  width: '24px',
  height: 'auto',
}
export const SwapIcon = AssetIconFactory<AssetIconProps>(swapIconProps)

export const SellIconPlaceholder = styled.div`
  display: flex;
  align-items: center;
  justify-content: center;
  width: 24px;
  height: 24px;
  border-radius: 100%;
  background-color: ${qora.color.neutral[40]};
  color: ${qora.color.container.background};
`

export const BuyIconPlaceholder = styled(SellIconPlaceholder)`
  background-color: ${qora.color.neutral[20]};
  color: ${qora.color.icon.default};
`

export const SwapPlaceholderIcon = styled(Icon).attrs({
  name: 'crypto-wallets',
})`
  --qora-icon-size: 16px;
`

export const TokenNameText = styled(Text)`
  line-height: 24px;
  color: ${qora.color.text.primary};
`

export const TokenSymbolText = styled(Text)`
  line-height: 18px;
  color: ${qora.color.text.tertiary};
`

export const AssetValueText = styled(Text)`
  line-height: 24px;
  color: ${qora.color.text.primary};
`

export const FiatValueText = styled(Text)`
  line-height: 18px;
  color: ${qora.color.text.tertiary};
`

export const ArrowIconWrapper = styled.div`
  display: flex;
  align-items: center;
  justify-content: center;
  background-color: ${qora.color.container.highlight};
  border-radius: 100%;
  width: 12px;
  height: 12px;
`

export const ArrowIcon = styled(Icon).attrs({
  name: 'carat-right',
})`
  --qora-icon-size: 12px;
  color: ${qora.color.icon.default};
`

export const IconWrapper = styled(Column)`
  position: relative;
`

export const SwapIconsWrapper = styled(Column)`
  position: relative;
  width: 32px;
  height: 32px;
`

export const SwapSellIcon = styled.div`
  display: flex;
  align-items: center;
  justify-content: center;
  position: absolute;
  top: 0px;
  right: 0px;
`

export const SwapBuyIcon = styled.div`
  display: flex;
  align-items: center;
  justify-content: center;
  position: absolute;
  bottom: 0px;
  left: 0px;
`

export const NetworkIconWrapper = styled.div`
  display: flex;
  align-items: center;
  justify-content: center;
  position: absolute;
  bottom: -2px;
  right: -2px;
  width: 18px;
  height: 18px;
  background-color: ${qora.color.container.background};
  border-radius: 100%;
`

export const StatusBubble = styled.div<{
  status: QoraiWallet.TransactionStatus
}>`
  display: flex;
  align-items: center;
  justify-content: center;
  border-radius: 100%;
  border: 2px solid ${qora.color.container.background};
  width: 16px;
  height: 16px;
  position: absolute;
  top: -5px;
  left: -2px;
  background-color: ${(p) =>
    p.status === QoraiWallet.TransactionStatus.Error
    || p.status === QoraiWallet.TransactionStatus.Dropped
      ? qora.color.systemfeedback.errorIcon
      : p.status === QoraiWallet.TransactionStatus.Unapproved
        ? qora.color.neutral[20]
        : qora.color.systemfeedback.infoIcon};
`

export const LoadingIcon = styled(ProgressRing)`
  --qora-progressring-size: 10px;
  --qora-progressring-color: ${qora.color.white};
`

export const StatusIcon = styled(Icon)`
  --qora-icon-size: 14px;
  color: ${qora.color.white};
`

export const BalancesColumn = styled(Column)`
  flex-wrap: wrap;
`
