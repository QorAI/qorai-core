// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import Icon from '@qorai/qora/react/icon'
import * as qora from '@qorai/qora/tokens/css/variables'

// Shared Styles
import { WalletButton, Row } from '../../../../../components/shared/style'

export const Wrapper = styled(Row)<{ type?: 'error' | 'warning' | 'info' }>`
  background-color: ${(p) =>
    p.type === 'error'
      ? qora.color.systemfeedback.errorBackground
      : p.type === 'warning'
        ? qora.color.systemfeedback.warningBackground
        : qora.color.systemfeedback.infoBackground};
  border-radius: 8px;
`

export const LearnMoreLink = styled.a`
  font-family: 'Poppins';
  font-style: normal;
  font-weight: 600;
  font-size: 12px;
  line-height: 20px;
  color: ${(p) => p.theme.color.interactive05};
  margin: 0px;
  padding: 0px;
  text-decoration: none;
  cursor: pointer;
  @media (prefers-color-scheme: dark) {
    color: ${(p) => p.theme.color.interactive06};
  }
`

export const HowToSolveButton = styled(WalletButton)`
  cursor: pointer;
  outline: none;
  background: none;
  border: none;
  font-family: 'Poppins';
  font-style: normal;
  font-weight: 600;
  font-size: 12px;
  line-height: 20px;
  color: ${(p) => p.theme.color.interactive05};
  margin: 0px;
  @media (prefers-color-scheme: dark) {
    color: ${(p) => p.theme.color.interactive06};
  }
`

export const ErrorIcon = styled(Icon)<{ type: 'error' | 'warning' }>`
  --qora-icon-size: 20px;
  color: ${(p) =>
    p.type === 'error'
      ? qora.color.systemfeedback.errorIcon
      : qora.color.systemfeedback.warningIcon};
  margin-right: 16px;
`
