// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Dropdown from '@qorai/qora/react/dropdown'

// Shared Styles
import { Row } from '../style'

export const DropdownOption = styled(Row)<{
  isDisabled?: boolean
}>`
  opacity: ${(p) => (p.isDisabled ? 0.6 : 1)};
`

export const DropdownFilter = styled(Dropdown)`
  width: 100%;
  color: ${qora.color.text.primary};
`
