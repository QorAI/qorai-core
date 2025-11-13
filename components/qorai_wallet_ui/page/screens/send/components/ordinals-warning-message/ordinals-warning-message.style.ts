// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'

// Qora styles
import * as qora from '@qorai/qora/tokens/css/variables'

// Qora icons
import Icon from '@qorai/qora/react/icon'

// Shared Styles
import { Row } from '../../shared.styles'

export const StyledRow = styled(Row)`
  width: 100%;
  padding: ${qora.spacing.m};
  gap: 10px;
  background-color: ${qora.color.systemfeedback.warningBackground};
  border-radius: ${qora.radius.m};
  margin-top: ${qora.spacing.xl};
  margin-bottom: ${qora.spacing.xl};
`

export const WarningIcon = styled(Icon).attrs({
  name: 'warning-triangle-filled',
})`
  --qora-icon-size: 20px;
  color: ${qora.color.systemfeedback.warningIcon};
`

export const CheckboxWrapper = styled.div`
  display: flex;
  align-items: center;
  margin-left: -8px;
`
