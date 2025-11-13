// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Icon from '@qorai/qora/react/icon'

export const PasswordMatchRow = styled.div`
  display: flex;
  flex-direction: row;
  align-items: center;
  justify-content: flex-start;
  width: 100%;
  height: 20px;
`

export const PasswordValidationText = styled.p<{ isMatch: boolean }>`
  color: ${(p) =>
    p.isMatch
      ? qora.color.text.interactive
      : qora.color.systemfeedback.errorText};
  font: ${qora.font.small.regular};
  margin: 0;
  padding: 0;
`

export const PasswordValidationIcon = styled(Icon)<{ isMatch: boolean }>`
  --qora-icon-size: 14px;
  --qora-icon-color: ${(p) =>
    p.isMatch
      ? qora.color.text.interactive
      : qora.color.systemfeedback.errorIcon};

  display: inline-block;
  margin-right: 4px;
  vertical-align: middle;
`

export const TooltipWrapper = styled.div`
  display: flex;
  position: relative;
  flex-direction: row;
  justify-content: flex-end;
  width: calc(100% - 90px);
`
