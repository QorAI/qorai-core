// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Icon from '@qorai/qora/react/icon'

// Shared Styles
import { WalletButton, Column, Text, Row } from '../../shared/style'

export const StyledWrapper = styled(Column)`
  background-color: ${qora.color.page.background};
`

export const HeaderText = styled(Text)`
  font: ${qora.font.heading.h4};
  letter-spacing: ${qora.typography.letterSpacing.large};
`

export const Title = styled(Text)`
  font: ${qora.font.heading.h3};
  letter-spacing: ${qora.typography.letterSpacing.headings};
`

export const Description = styled(Text)`
  font: ${qora.font.default.regular};
  letter-spacing: ${qora.typography.letterSpacing.default};
`

export const NetworkInfoBox = styled(Column)`
  background-color: ${qora.color.container.highlight};
  border-radius: ${qora.radius.xl};
`

export const NetworkInfoLabel = styled(Text)`
  font: ${qora.font.small.regular};
  letter-spacing: ${qora.typography.letterSpacing.small};
`

export const NetworkInfoText = styled(Text)`
  font: ${qora.font.default.semibold};
  letter-spacing: ${qora.typography.letterSpacing.default};
`

export const DividerWrapper = styled(Row)`
  align-items: center;
  justify-content: center;
  position: relative;
`

export const ArrowIconWrapper = styled.div`
  display: flex;
  align-items: center;
  justify-content: center;
  position: absolute;
  width: 24px;
  height: 24px;
  background-color: ${qora.color.container.background};
  border: 1px solid ${qora.color.divider.subtle};
  border-radius: 100%;
`

export const ArrowIcon = styled(Icon).attrs({
  name: 'carat-down',
})`
  --qora-icon-size: 16px;
  color: ${qora.color.icon.default};
`

export const DetailsButton = styled(WalletButton)`
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

export const LearnMoreButton = styled(DetailsButton)`
  font: ${qora.font.default.semibold};
  letter-spacing: ${qora.typography.letterSpacing.default};
`

export const Card = styled(Column)`
  background-color: ${qora.color.container.background};
  border-radius: ${qora.radius.xl};
  box-shadow: ${qora.effect.elevation['01']};
  overflow: hidden;
`
