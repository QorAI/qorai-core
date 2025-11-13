// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'

// Shared Styles
import { Column, Row, Text } from '../../../shared/style'

export const StyledWrapper = styled(Column)`
  overflow: hidden;
`

export const Card = styled(Column)`
  background-color: ${qora.color.container.highlight};
  border-radius: ${qora.radius.xl};
`

export const Description = styled(Text)`
  font: ${qora.font.small.semibold};
  letter-spacing: ${qora.typography.letterSpacing.small};
`

export const SectionLabel = styled(Text)`
  font: ${qora.font.small.semibold};
  letter-spacing: ${qora.typography.letterSpacing.small};
`

export const InputWrapper = styled(Row)<{
  hasError?: boolean
}>`
  cursor: pointer;
  background-color: ${qora.color.container.background};
  outline: 1px solid
    ${(p) =>
      p.hasError
        ? qora.color.systemfeedback.errorVibrant
        : qora.color.divider.subtle};
  transition:
    outline 0.1s ease-in-out,
    box-shadow 0.1s ease-in-out;
  border-radius: ${qora.radius.m};
  :hover {
    outline: 1px solid ${qora.color.divider.strong};
    box-shadow: ${qora.effect.elevation['02']};
  }
  :focus-within {
    outline: 2px solid
      ${(p) =>
        p.hasError
          ? qora.color.systemfeedback.errorVibrant
          : qora.color.primary[40]};
  }
`

export const Input = styled.input`
  font: ${qora.font.small.regular};
  letter-spacing: ${qora.typography.letterSpacing.small};
  background-color: ${qora.color.container.background};
  color: ${qora.color.text.primary};
  outline: none;
  border: none;
  width: 100%;
  padding: 0px;
  text-align: right;
  ::placeholder {
    font: ${qora.font.small.regular};
    letter-spacing: ${qora.typography.letterSpacing.small};
    color: ${qora.color.text.tertiary};
  }
  :focus {
    outline: none;
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

export const InputLabel = styled(Text)`
  font: ${qora.font.small.regular};
  letter-spacing: ${qora.typography.letterSpacing.small};
`
