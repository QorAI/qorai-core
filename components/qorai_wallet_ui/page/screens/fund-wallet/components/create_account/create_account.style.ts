// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import QoraInput from '@qorai/qora/react/input'
import QoraDialog from '@qorai/qora/react/dialog'
import {
  layoutPanelWidth, //
} from '../../../../../components/desktop/wallet-page-wrapper/wallet-page-wrapper.style'

export const Dialog = styled(QoraDialog).attrs({
  size: window.innerWidth <= layoutPanelWidth ? 'mobile' : 'normal',
})`
  --qora-dialog-padding: 32px;
  --qora-dialog-width: 600px;
  --qora-dialog-backdrop-filter: blur(8px);
`

export const Input = styled(QoraInput)`
  width: 100%;
  max-width: 400px;
`
