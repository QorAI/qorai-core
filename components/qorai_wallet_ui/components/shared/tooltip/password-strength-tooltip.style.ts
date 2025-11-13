// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'

import QoraTooltip from '@qorai/qora/react/tooltip'
import Icon from '@qorai/qora/react/icon'
import * as qora from '@qorai/qora/tokens/css/variables'

export const Tooltip = styled(QoraTooltip)`
  --qora-tooltip-background: ${qora.color.container.background};
  --qora-tooltip-text-color: red;
  --qora-tooltip-padding: 16px;
  border-radius: ${qora.spacing.none};
  --qora-tooltip-shadow:
    0px 4px 16px -2px rgba(0, 0, 0, 0.1), 0px 1px 0px 0px rgba(0, 0, 0, 0.05);
`

export const CriteriaCheckContainer = styled.div`
  width: 100%;
  display: flex;
  flex: 1;
  flex-direction: row;
  align-items: center;
  justify-content: flex-start;
  gap: 4px;
`

export const PasswordStrengthText = styled.p<{ isStrong?: boolean }>`
  font: ${qora.font.default.regular};
  margin-bottom: 6px;
  vertical-align: middle;
  color: ${qora.color.text.primary};
  padding: 0;
  margin: 0;
`

export const PasswordStrengthHeading = styled(PasswordStrengthText)`
  font: ${qora.font.default.regular};
  color: ${qora.color.text.primary};
  margin-bottom: ${qora.spacing.xs};
`

export const GreenCheckmarkIcon = styled(Icon).attrs({
  name: 'check-circle-outline',
})`
  --qora-icon-size: ${qora.spacing.xl};
  --qora-icon-color: ${qora.color.systemfeedback.successIcon};
  margin-right: ${qora.spacing.s};
`

export const CloseCircleIcon = styled(Icon).attrs({
  name: 'close-circle',
})`
  --qora-icon-size: ${qora.spacing.xl};
  --qora-icon-color: ${qora.color.systemfeedback.errorIcon};
  margin-right: ${qora.spacing.s};
`
