// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'

// Shared Styles
import { Row, Text } from '../../shared/style'

export const Wrapper = styled(Row)`
  --qora-icon-size: 16px;
  --qora-icon-color: ${qora.color.systemfeedback.errorIcon};
  background-color: ${qora.color.systemfeedback.errorBackground};
`

export const ErrorText = styled(Text)`
  font: ${qora.font.small.regular};
  letter-spacing: ${qora.typography.letterSpacing.small};
`
