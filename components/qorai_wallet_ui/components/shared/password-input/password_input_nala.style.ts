// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import Input from '@qorai/qora/react/input'
import Icon from '@qorai/qora/react/icon'
import * as qora from '@qorai/qora/tokens/css/variables'

export const FullWidthInput = styled(Input)`
  width: 100%;
`

export const LockIcon = styled(Icon).attrs({ name: 'lock-plain' })`
  --qora-icon-size: 20px;
  color: ${qora.color.icon.default};
`
