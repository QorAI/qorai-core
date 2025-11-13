// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'

// styles
import { Column } from '../../shared/style'

export const alertItemGap = qora.spacing.m

export const TitleText = styled.h4`
  color: ${qora.color.text.primary};
  text-align: center;
  font: ${qora.font.heading.h4};
  padding: 8px 32px 0px 32px;
`

export const AlertTextContainer = styled.div`
  color: ${qora.color.systemfeedback.infoText};
  text-align: center;
  font: ${qora.font.small.regular};
`

export const SeeAvailableNetworksLink = styled.a`
  color: ${qora.color.text.interactive};
  text-align: center;
  font: ${qora.font.small.semibold};
  text-decoration: none;
  cursor: pointer;
`

export const FullWidthChildrenColumn = styled(Column)`
  & * {
    width: 100%;
  }
`
