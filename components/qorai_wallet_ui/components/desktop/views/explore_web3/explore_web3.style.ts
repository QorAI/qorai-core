// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Button from '@qorai/qora/react/button'
import Label from '@qorai/qora/react/label'
import Icon from '@qorai/qora/react/icon'

// styles
import {
  layoutPanelWidth, //
} from '../../wallet-page-wrapper/wallet-page-wrapper.style'

export const DappsGrid = styled.div`
  display: grid;
  grid-template-columns: repeat(2, 1fr);
  column-gap: ${qora.spacing['3Xl']};
  height: auto;

  @media screen and (max-width: ${layoutPanelWidth}px) {
    grid-template-columns: 1fr;
  }
`

export const CategoryHeader = styled.p`
  width: 100%;
  font: ${qora.font.heading.h4};
  color: ${qora.color.text.primary};
  text-align: left;
  text-transform: capitalize;
  padding: 0;
  margin: 0;
`

export const PlainButton = styled(Button).attrs({
  kind: 'plain',
})`
  --qora-button-color: ${qora.color.text.interactive};
  --qora-button-padding: 8px;
  white-space: nowrap;
`

export const FilterLabel = styled(Label).attrs({
  color: 'neutral',
  mode: 'default',
})`
  --qora-label-padding: 8px;
  --qora-label-icon-size: 14px;

  color: ${qora.color.neutral[50]};
  font: ${qora.font.xSmall.regular};
  font-weight: 700;
  text-transform: uppercase;
`

export const FilterClose = styled(Icon).attrs({
  name: 'close',
})`
  --qora-icon-size: 14px;
`

export const FilterButton = styled(Button).attrs({
  kind: 'plain-faint',
  size: 'tiny',
})`
  --qora-button-padding: 0;
  --qora-button-radius: 4px;
  flex-grow: 0;
  height: 20px;
`
