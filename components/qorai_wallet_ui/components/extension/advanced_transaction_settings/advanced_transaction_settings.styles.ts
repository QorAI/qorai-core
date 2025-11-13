// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'

// Shared Styles
import { Column, Text } from '../../shared/style'

export const StyledWrapper = styled(Column)`
  overflow: hidden;
`

export const LabelText = styled(Text)`
  font: ${qora.font.small.semibold};
  letter-spacing: ${qora.typography.letterSpacing.small};
`

export const DescriptionText = styled(Text)`
  font: ${qora.font.small.regular};
  letter-spacing: ${qora.typography.letterSpacing.small};
`

export const Input = styled.input<{
  hasError?: boolean
}>`
  font: ${qora.font.small.regular};
  letter-spacing: ${qora.typography.letterSpacing.small};
  background-color: ${qora.color.container.background};
  color: ${qora.color.text.primary};
  border: none;
  width: 100%;
  padding: 0px;
  outline: 1px solid ${qora.color.divider.subtle};
  transition:
    outline 0.1s ease-in-out,
    box-shadow 0.1s ease-in-out;
  border-radius: ${qora.radius.m};
  padding: 10px 12px;
  ::placeholder {
    font: ${qora.font.small.regular};
    letter-spacing: ${qora.typography.letterSpacing.small};
    color: ${qora.color.text.tertiary};
  }
  :hover {
    outline: 1px solid ${qora.color.divider.strong};
    box-shadow: ${qora.effect.elevation['02']};
  }
  :focus {
    outline: 2px solid ${qora.color.primary[40]};
  }
  ::-webkit-inner-spin-button {
    -webkit-appearance: none;
    margin: 0;
  }
  ::-webkit-outer-spin-button {
    -webkit-appearance: none;
    margin: 0;
  }
`

export const ButtonText = styled.span`
  display: flex;
  width: 80px;
  justify-content: center;
`
