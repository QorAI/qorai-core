// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Radio from '@qorai/qora/react/radioButton'
import Icon from '@qorai/qora/react/icon'

export const RadioButton = styled(Radio)<{
  isSelected: boolean
}>`
  width: 100%;
  padding: 0px 16px;
  background-color: ${(p) =>
    p.isSelected ? 'none' : qora.color.container.highlight};
  border-radius: 8px;
  outline: ${(p) =>
    p.isSelected ? `solid 2px ${qora.color.button.background}` : 'none'};
`

export const ProviderIcon = styled.img`
  height: 20px;
  width: auto;
  margin-right: 8px;
`

export const InfoIcon = styled(Icon).attrs({
  name: 'info-outline',
})`
  --qora-icon-size: 15px;
  color: ${qora.color.icon.default};
`
