// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'

// Shared Styles
import { Column, Text } from '../../shared/style'

export const StyledWrapper = styled(Column)`
  background-color: ${qora.color.container.highlight};
  border-radius: ${qora.radius.xl};
`

export const SectionLabel = styled(Text)`
  font: ${qora.font.default.regular};
  letter-spacing: ${qora.typography.letterSpacing.default};
`

export const SectionDetails = styled(Text)`
  font: ${qora.font.default.semibold};
  letter-spacing: ${qora.typography.letterSpacing.default};
`
