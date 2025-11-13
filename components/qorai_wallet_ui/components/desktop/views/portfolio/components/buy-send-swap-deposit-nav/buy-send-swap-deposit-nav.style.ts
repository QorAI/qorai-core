// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Icon from '@qorai/qora/react/icon'
import { WalletButton, Column } from '../../../../../shared/style'

export const ButtonWrapper = styled(Column)`
  margin-right: 28px;
  &:last-child {
    margin-right: 0px;
  }
`

export const Button = styled(WalletButton)<{
  minWidth?: number
}>`
  display: flex;
  align-items: center;
  justify-content: center;
  cursor: pointer;
  width: 48px;
  height: 48px;
  border-radius: 16px;
  outline: none;
  border: none;
  background: none;
  margin-bottom: 4px;
  background-color: transparent;
  background-color: ${qora.color.button.background};
`

export const ButtonIcon = styled(Icon)`
  --qora-icon-size: 24px;
  color: ${qora.color.white};
  @media (prefers-color-scheme: dark) {
    color: ${qora.color.schemes.onPrimary};
  }
`

export const ButtonText = styled.span`
  font-family: Poppins;
  font-style: normal;
  font-size: 12px;
  font-weight: 600;
  line-height: 20px;
  color: ${qora.color.text.primary};
`

export const MoreMenuWrapper = styled(ButtonWrapper)`
  position: relative;
`
