// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'

// Shared Styles
import { Column, Row, Text } from '../../shared/style'
import { ConfirmationButtonLink } from '../shared-panel-styles'

export const StyledWrapper = styled(Column)`
  background-color: ${qora.color.page.background};
`

export const ContentWrapper = styled(Column)`
  overflow: hidden;
`

export const Title = styled(Row)`
  font: ${qora.font.heading.h4};
  letter-spacing: ${qora.typography.letterSpacing.headings};
  color: ${qora.color.text.primary};
`

export const Description = styled(Text)`
  font: ${qora.font.small.regular};
  letter-spacing: ${qora.typography.letterSpacing.small};
`

export const Card = styled(Column)`
  background-color: ${qora.color.container.background};
  border-radius: ${qora.radius.xl};
  box-shadow: ${qora.effect.elevation['01']};
  overflow: hidden;
`

export const InfoBox = styled(Column)`
  background-color: ${qora.color.container.highlight};
  border-radius: ${qora.radius.xl};
  overflow: hidden;
`

export const AmountText = styled(Text)`
  font: ${qora.font.small.semibold};
  letter-spacing: ${qora.typography.letterSpacing.small};
`

export const TokenButtonLink = styled(ConfirmationButtonLink)`
  font: ${qora.font.heading.h4};
  letter-spacing: ${qora.typography.letterSpacing.headings};
`
