// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'

import * as qora from '@qorai/qora/tokens/css/variables'
import Button from '@qorai/qora/react/button'

export const FullScreenPanelPopupWrapper = styled.div<{
  kind?: 'danger'
}>`
  position: absolute;
  top: 0;
  bottom: 0;
  left: 0;
  right: 0;

  background-color: ${(p) =>
    p.kind === 'danger' ? qora.color.systemfeedback.errorBackground : 'unset'};
  color: ${(p) =>
    p.kind === 'danger' ? qora.color.systemfeedback.errorBackground : 'unset'};
  box-shadow: ${qora.effect.elevation['05']};
`

export const IconButton = styled(Button)`
  background: none;
  border: none;
`
