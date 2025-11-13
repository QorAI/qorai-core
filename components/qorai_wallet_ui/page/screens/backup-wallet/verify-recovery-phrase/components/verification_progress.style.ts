// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import Alert from '@qorai/qora/react/alert'
import * as qora from '@qorai/qora/tokens/css/variables'

export const Wrapper = styled.span`
  display: inline-flex;
  align-items: center;
  justify-content: center;
  gap: 4px;
`

export const Rectangle = styled.span<{
  isActive: boolean
  width: string
}>`
  width: ${(p) => p.width};
  height: 8px;
  border-radius: 4px;
  background-color: ${(p) =>
    p.isActive ? qora.color.button.background : qora.color.purple[20]};
`

export const InfoAlert = styled(Alert).attrs({
  kind: 'info',
  mode: 'simple',
})`
  --qora-alert-center-position: 'center';
  --qora-alert-center-width: '100%';
  width: 100%;

  qora-alert {
    align-items: center;
  }
`
