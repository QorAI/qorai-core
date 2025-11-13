// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Icon from '@qorai/qora/react/icon'

// Shared Styles
import { Text } from '../../../../../components/shared/style'

export const PercentChangeText = styled(Text)<{
  isDown: boolean
}>`
  color: ${(p) =>
    p.isDown
      ? qora.color.systemfeedback.errorText
      : qora.color.systemfeedback.successText};
`

export const CopyIcon = styled(Icon).attrs({
  name: 'copy',
})`
  --qora-icon-size: 16px;
  color: ${qora.color.icon.default};
`
