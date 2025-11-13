// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Dropdown from '@qorai/qora/react/dropdown'
import QoraIcon from '@qorai/qora/react/icon'

// Constants
import { layoutPanelWidth } from '../../../wallet-page-wrapper/wallet-page-wrapper.style'

// Shared Styles
import { Row, Column, WalletButton, Text } from '../../../../shared/style'

export const CheckboxRow = styled(Row)`
  flex-wrap: wrap;
  @media screen and (max-width: ${layoutPanelWidth}px) {
    flex-direction: column;
    align-items: flex-start;
  }
`

export const CheckboxWrapper = styled(Row)`
  min-width: 50%;
`

export const SelectAllButton = styled(WalletButton)`
  cursor: pointer;
  outline: none;
  border: none;
  background: none;
  padding: 0px;
  font-family: Poppins;
  font-size: 12px;
  letter-spacing: 0.03em;
  line-height: 16px;
  font-weight: 600;
  color: ${qora.color.text.interactive};
`

export const Title = styled(Text)`
  color: ${qora.color.text.primary};
  line-height: 28px;
`

export const Description = styled(Text)`
  color: ${qora.color.text.secondary};
  line-height: 18px;
`

export const CheckboxText = styled(Text)`
  color: ${qora.color.text.primary};
  line-height: 24px;
`

export const IconWrapper = styled(Column)`
  width: 32px;
  height: 32px;
  background-color: ${qora.color.container.highlight};
  border-radius: 100%;
  margin-right: 16px;
`

export const Icon = styled(QoraIcon)`
  --qora-icon-size: 16px;
  color: ${qora.color.icon.default};
`

export const DropdownFilter = styled(Dropdown)`
  min-width: 40%;
  color: ${qora.color.text.primary};
`
