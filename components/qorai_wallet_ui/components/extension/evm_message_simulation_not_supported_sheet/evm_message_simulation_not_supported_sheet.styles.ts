// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Icon from '@qorai/qora/react/icon'

// styles
import { Column, WalletButton } from '../../shared/style'

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

export const CollapseTitle = styled.div`
  display: inline-flex;
  flex-direction: row;
  align-items: center;
  justify-content: center;
  color: ${qora.color.text.interactive};
  text-align: center;
  font: ${qora.font.small.semibold};
  text-decoration: none;
  cursor: pointer;
  width: 100%;
`

export const CollapseIcon = styled(Icon)`
  max-width: 16px;
  --qora-icon-size: 16px;
  --qora-icon-color: ${qora.color.icon.interactive};
  margin-left: 4px;
`

export const CollapseTitleRow = styled(WalletButton)`
  cursor: pointer;
  font-family: 'Poppins';
  display: flex;
  flex-direction: row;
  align-items: center;
  justify-content: center;
  width: 100%;
  position: relative;
  box-sizing: border-box;
  background: none;
  border: none;
`

export const FullWidthChildrenColumn = styled(Column)`
  & * {
    width: 100%;
  }
`
