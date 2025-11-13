// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'

// Shared Styles
import {
  Column,
  AssetIconProps,
  AssetIconFactory,
  WalletButton,
  Text,
} from '../../shared/style'

export const StyledWrapper = styled(Column)`
  background-color: ${qora.color.page.background};
`

export const HeaderText = styled(Text)`
  font: ${qora.font.heading.h4};
  letter-spacing: ${qora.typography.letterSpacing.headings};
`

export const Card = styled(Column)`
  background-color: ${qora.color.container.background};
  border-radius: ${qora.radius.xl};
  box-shadow: ${qora.effect.elevation['01']};
  overflow: hidden;
`

export const Description = styled(Text)`
  font: ${qora.font.heading.h3};
  letter-spacing: ${qora.typography.letterSpacing.headings};
`

export const TokenName = styled(Text)`
  font: ${qora.font.large.semibold};
  letter-spacing: ${qora.typography.letterSpacing.default};
`

export const TokenDescription = styled(Text)`
  font: ${qora.font.large.regular};
  letter-spacing: ${qora.typography.letterSpacing.default};
`

export const ContractAddress = styled(WalletButton)`
  font: ${qora.font.small.semibold};
  letter-spacing: ${qora.typography.letterSpacing.small};
  color: ${qora.color.text.interactive};
  background: none;
  cursor: pointer;
  outline: none;
  border: none;
  margin: 0px;
  padding: 0px;
`

export const AssetIcon = AssetIconFactory<AssetIconProps>({
  width: '80px',
  height: 'auto',
  marginBottom: '8px',
})
