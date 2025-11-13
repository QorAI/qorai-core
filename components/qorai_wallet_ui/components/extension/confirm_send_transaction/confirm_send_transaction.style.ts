// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'

// Shared Styles
import { Column, Text } from '../../shared/style'

export const StyledWrapper = styled(Column)`
  background-color: ${qora.color.page.background};
`

export const Card = styled(Column)`
  background-color: ${qora.color.container.background};
  border-radius: ${qora.radius.xl};
  box-shadow: ${qora.effect.elevation['01']};
  overflow: hidden;
`

export const InfoBox = styled(Column)`
  background-color: ${qora.color.container.highlight};
  border-radius: ${qora.radius.xl};
  overflow: hidden;
`

export const Title = styled(Text)`
  font: ${qora.font.heading.h4};
  letter-spacing: ${qora.typography.letterSpacing.large};
`
