// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'

// Shared Styles
import { Row, Text } from '../../shared/style'

export const StyledWrapper = styled(Row)<{
  noBackground?: boolean
  orientation?: 'horizontal' | 'vertical'
}>`
  background-color: ${({ noBackground }) =>
    noBackground ? 'transparent' : qora.color.container.highlight};
  flex-direction: ${({ orientation }) =>
    orientation === 'vertical' ? 'column' : 'row'};
`

export const FavIcon = styled.img<{ bigger?: boolean }>`
  width: ${({ bigger }) => (bigger ? '56px' : '48px')};
  height: ${({ bigger }) => (bigger ? '56px' : '48px')};
  border-radius: 8px;
  background-color: ${qora.color.container.background};
  border: 1px solid ${qora.color.divider.subtle};
  padding: ${({ bigger }) => (bigger ? qora.spacing.m : qora.spacing.s)};
`

export const OriginName = styled(Text)`
  font: ${qora.font.default.semibold};
  letter-spacing: ${qora.typography.letterSpacing.default};
  word-break: break-word;
`

export const OriginUrl = styled(Text)`
  font: ${qora.font.small.regular};
  letter-spacing: ${qora.typography.letterSpacing.small};
  word-break: break-word;
`
