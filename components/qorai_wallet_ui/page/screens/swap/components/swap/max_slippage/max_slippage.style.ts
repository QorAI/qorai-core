// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Input from '@qorai/qora/react/input'
import Icon from '@qorai/qora/react/icon'

// Shared Styles
import {
  WalletButton, //
} from '../../../../../../components/shared/style'

export const OptionButton = styled(WalletButton)<{
  isSelected: boolean
}>`
  cursor: pointer;
  display: flex;
  flex-direction: row;
  justify-content: space-between;
  background: none;
  background-color: ${(p) =>
    p.isSelected ? 'none' : qora.color.container.highlight};
  outline: ${(p) =>
    p.isSelected ? `solid 2px ${qora.color.button.background}` : 'none'};
  border: none;
  border-radius: 8px;
  width: 100%;
  height: 100%;
  min-height: 95px;
  padding: 12px;
`

export const CustomInput = styled(Input)`
  max-width: 100px;
  text-align: right;
  --qora-control-icon-size: 14px;
`

export const RadioIcon = styled(Icon)<{
  isSelected: boolean
}>`
  --qora-icon-size: 20px;
  color: ${(p) =>
    p.isSelected ? qora.color.icon.interactive : qora.color.icon.default};
`
