// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import Icon from '@qorai/qora/react/icon'
import Dropdown from '@qorai/qora/react/dropdown'
import * as qora from '@qorai/qora/tokens/css/variables'

export const LockIconContainer = styled.div`
  display: flex;
  flex-direction: row;
  align-items: center;
  justify-content: center;
  min-width: 30px;
  height: 30px;
  background-color: ${qora.color.container.interactive};
  border-radius: 50%;
`

export const LockIcon = styled(Icon).attrs({
  name: 'lock',
})`
  --qora-icon-size: ${qora.icon.xs};
  color: ${qora.color.icon.interactive};
`

export const SettingDescription = styled.div`
  font: ${qora.font.default.regular};
  white-space: nowrap;
  color: ${qora.color.text.primary};
`

export const DurationDropdown = styled(Dropdown)`
  min-width: 136px;
`

export const OptionLabel = styled.div`
  color: ${qora.color.text.primary};
`
