// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import QoraIcon from '@qorai/qora/react/icon'

// Shared Styles
import { Text } from '../../shared/style'

export const LoginWrapper = styled.div`
  display: flex;
  align-items: center;
  justify-content: space-between;
  flex-direction: row;
  background-color: ${qora.color.systemfeedback.infoBackground};
  border-radius: 8px;
  padding: 8px 16px;
  width: 100%;
`

export const InfoText = styled(Text)`
  line-height: 24px;
  color: ${qora.color.text.tertiary};
  padding: 6px 0px;
`

export const InfoIcon = styled(QoraIcon).attrs({
  name: 'warning-circle-filled',
})`
  --qora-icon-size: 20px;
  color: ${qora.color.systemfeedback.infoIcon};
  margin-right: 16px;
`

export const ButtonWrapper = styled.div`
  min-width: 42px;
`
