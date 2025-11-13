// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import QoraButton from '@qorai/qora/react/button'
import QoraButtonMenu from '@qorai/qora/react/buttonMenu'

export const Button = styled(QoraButton)`
  --qora-button-color: ${qora.color.button.errorBackground};
`

export const ButtonMenu = styled(QoraButtonMenu)`
  --qora-menu-control-width: 900px;
  qora-menu-item {
    padding: 8px;
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: flex-start;
    gap: 8px;
    color: ${qora.color.text.primary};
  }
  qora-menu-item:first-of-type {
    margin-top: 4px;
  }
  qora-menu-item:last-of-type {
    color: ${qora.color.systemfeedback.errorText};
  }
`

export const StyledMenuItem = styled
