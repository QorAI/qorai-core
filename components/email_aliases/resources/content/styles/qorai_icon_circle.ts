// Copyright (c) 2025 The QorAI Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import { color } from '@qorai/qora/tokens/css/variables'
import Icon from '@qorai/qora/react/icon'
import styled from 'styled-components'

const QorAIIconCircle = styled(Icon)`
  --qora-icon-size: 24px;
  align-items: center;
  border-radius: 100px;
  border: ${color.divider.subtle} 1px solid;
  display: flex;
  justify-content: center;
  min-height: 40px;
  min-width: 40px;
  flex-grow: 0;
`

export default QorAIIconCircle
