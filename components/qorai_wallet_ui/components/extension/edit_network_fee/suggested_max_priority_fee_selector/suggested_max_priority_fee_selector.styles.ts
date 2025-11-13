// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Icon from '@qorai/qora/react/icon'

// Shared Styles
import { Column, WalletButton, Text } from '../../../shared/style'

export const StyledWrapper = styled(Column)`
  overflow: hidden;
`

export const FeeOptionButton = styled(WalletButton)<{
  isSelected: boolean
}>`
  display: flex;
  flex-direction: column;
  align-items: flex-start;
  justify-content: flex-start;
  background: none;
  cursor: pointer;
  outline: none;
  margin: 0px;
  background-color: ${({ isSelected }) =>
    isSelected
      ? qora.color.container.background
      : qora.color.container.highlight};
  border-radius: ${qora.radius.m};
  border: 2px solid
    ${({ isSelected }) =>
      isSelected ? qora.color.button.background : 'transparent'};
  padding: 12px;
  width: 100%;
`

export const NameText = styled(Text)`
  font: ${qora.font.small.semibold};
  letter-spacing: ${qora.typography.letterSpacing.small};
`

export const TimeText = styled(Text)`
  font: ${qora.font.heading.h4};
  letter-spacing: ${qora.typography.letterSpacing.large};
`

export const FeeAmountText = styled(Text)`
  font: ${qora.font.xSmall.semibold};
  letter-spacing: ${qora.typography.letterSpacing.small};
  word-break: break-all;
`

export const FiatAmountText = styled(Text)`
  font: ${qora.font.small.regular};
  letter-spacing: ${qora.typography.letterSpacing.small};
`

export const RadioIcon = styled(Icon)<{
  isSelected: boolean
}>`
  --qora-icon-size: 18px;
  --qora-icon-color: ${({ isSelected }) =>
    isSelected ? qora.color.icon.interactive : qora.color.icon.disabled};
`
