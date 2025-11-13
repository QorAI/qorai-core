// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import Button from '@qorai/qora/react/button'
import Tooltip from '@qorai/qora/react/tooltip'
import * as qora from '@qorai/qora/tokens/css/variables'

// Shared Styles
import {
  AssetIconFactory,
  AssetIconProps,
  Text,
  Column,
  WalletButton,
} from '../../shared/style'
import { ConfirmationButtonLink } from '../shared-panel-styles'

export const IconsWrapper = styled(Column)`
  position: relative;
`

export const AssetIcon = AssetIconFactory<AssetIconProps>({
  width: '40px',
  height: 'auto',
})

export const NetworkIconWrapper = styled.div`
  display: flex;
  position: absolute;
  bottom: -2px;
  right: -2px;
  background-color: ${qora.color.container.background};
  border-radius: 100%;
  padding: 2px;
`

export const TokenAmountText = styled(Text)`
  font: ${qora.font.heading.h3};
  letter-spacing: ${qora.typography.letterSpacing.headings};
`

export const AccountButton = styled(WalletButton)`
  cursor: pointer;
  padding: 0px;
  margin: 0px;
  outline: none;
  border: none;
  background: transparent;
`

export const ArrowIconContainer = styled.div`
  display: flex;
  align-items: center;
  justify-content: center;
  min-width: 40px;
  min-height: 40px;
  border-radius: 100%;
  background-color: ${qora.color.page.background};
  --qora-icon-size: 16px;
  --qora-icon-color: ${qora.color.icon.default};
`

export const AddressText = styled(Text)`
  font: ${qora.font.large.semibold};
  letter-spacing: ${qora.typography.letterSpacing.large};
`

export const WarningTooltip = styled(Tooltip)`
  --qora-icon-size: 16px;
  --qora-icon-color: ${qora.color.icon.default};
`

export const WarningTooltipContent = styled(Column)`
  white-space: pre-line;
`

export const LearnMoreButton = styled(ConfirmationButtonLink)`
  display: inline-flex;
`

export const BlockExplorerButton = styled(Button)`
  --qora-icon-size: 20px;
  color: ${qora.color.icon.default};
`
