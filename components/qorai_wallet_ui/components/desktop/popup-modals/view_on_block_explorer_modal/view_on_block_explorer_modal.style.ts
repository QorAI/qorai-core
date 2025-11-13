// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Icon from '@qorai/qora/react/icon'

// Shared Styled
import { Row, WalletButton, Column, Text } from '../../../shared/style'

export const StyledWrapper = styled(Column)`
  overflow: hidden;
`

export const AccountInfoRow = styled(Row)`
  background-color: ${qora.color.container.highlight};
  border-radius: ${qora.radius.xl};
  padding: 8px;
`

export const AddressText = styled(Text)`
  word-break: break-all;
`

export const Button = styled(WalletButton)`
  cursor: pointer;
  display: flex;
  flex-direction: row;
  justify-content: space-between;
  align-items: center;
  background: none;
  background-color: none;
  outline: none;
  border: none;
  border-radius: ${qora.radius.m};
  width: 100%;
  padding: 16px;
  --icon-display: none;
  &:hover {
    background-color: ${qora.color.container.highlight};
    --icon-display: block;
  }
`

export const LaunchIcon = styled(Icon).attrs({
  name: 'launch',
})`
  display: var(--icon-display);
  --qora-icon-size: 16px;
  color: ${qora.color.icon.interactive};
`
