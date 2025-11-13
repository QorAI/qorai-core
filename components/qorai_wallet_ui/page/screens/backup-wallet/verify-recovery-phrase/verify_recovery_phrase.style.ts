// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import Input from '@qorai/qora/react/input'
import Alert from '@qorai/qora/react/alert'
import Button from '@qorai/qora/react/button'
import Icon from '@qorai/qora/react/icon'
import * as qora from '@qorai/qora/tokens/css/variables'

export const ErrorTextRow = styled.div<{
  hasError: boolean
}>`
  display: flex;
  flex-direction: row;
  align-items: center;
  justify-content: center;
  height: ${(p) => (p.hasError ? 'auto' : '38px')};
  margin-top: 20px;
  padding-top: 10px;
  margin-bottom: 12px;
`

export const FormLabel = styled.span`
  font: ${qora.font.default.regular};
  color: ${qora.color.text.primary};
`

export const Bold = styled(FormLabel)`
  font-weight: 600;
`

export const FormInput = styled(Input).attrs({
  mode: 'filled',
})`
  width: 100%;
`

export const ErrorAlert = styled(Alert).attrs({
  kind: 'error',
  mode: 'simple',
})`
  --qora-alert-center-position: 'center';
  --qora-alert-center-width: '100%';
  width: 100%;

  qora-alert {
    align-items: center;
  }
`

export const CloseButton = styled(Button).attrs({
  kind: 'plain',
})`
  --qora-button-padding: 0;
  height: 20px;
  padding-top: 2px;
`

export const CloseIcon = styled(Icon).attrs({
  name: 'close',
})`
  --qora-icon-color: ${qora.color.systemfeedback.errorIcon};
`

export const BackButton = styled(Button).attrs({
  kind: 'plain',
})`
  width: '100%';
`
