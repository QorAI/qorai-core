// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'

import { Column } from '../../shared/style'
import Icon from '@qorai/qora/react/icon'

export const LargeWarningCircleIcon = styled(Icon).attrs({
  name: 'warning-circle-filled',
})`
  --qora-icon-size: 40px;
  color: ${qora.color.systemfeedback.errorIcon};
`

export const FullWidthChildrenColumn = styled(Column)`
  align-self: flex-end;
  justify-self: flex-end;
  & * {
    width: 100%;
  }
`

export const WarningButtonText = styled.span`
  color: ${qora.color.systemfeedback.errorIcon};
`

export const CriticalWarningTitle = styled.span`
  color: ${qora.color.text.primary};
  text-align: center;
  font: ${qora.font.default.semibold};
`

export const CriticalWarningDescription = styled.span`
  color: ${qora.color.text.primary};
  text-align: center;
  font: ${qora.font.small.regular};
`
