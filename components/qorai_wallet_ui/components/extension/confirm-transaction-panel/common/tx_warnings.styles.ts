// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'

import Button from '@qorai/qora/react/button'
import Icon from '@qorai/qora/react/icon'
import Collapse from '@qorai/qora/react/collapse'

// shared styles
import { styledScrollbarMixin } from '../../../shared/style'

interface WarningProps {
  isCritical?: boolean
}

export const WarningCloseIcon = styled(Icon).attrs({
  name: 'close',
})`
  --qora-icon-size: 20px;
`

export const WarningButton = styled(Button)<
  WarningProps & { isInfo?: boolean }
>`
  --qora-button-color: ${(p) =>
    p.isInfo
      ? qora.color.systemfeedback.infoIcon
      : p.isCritical
        ? qora.color.systemfeedback.errorIcon
        : qora.color.systemfeedback.warningIcon};
`

export const WarningCollapse = styled(Collapse)<WarningProps>`
  --qora-collapse-summary-padding: 12px 16px;
  --qora-collapse-content-padding: ${qora.spacing.m} ${qora.spacing['2Xl']};

  --qora-collapse-radius: ${qora.radius.m};
  --qora-collapse-shadow: none;
  --qora-collapse-border-color: none;

  --qora-collapse-background-color: ${(p) =>
    p.isCritical
      ? qora.color.systemfeedback.errorBackground
      : qora.color.systemfeedback.warningBackground};

  --qora-collapse-icon-color: ${(p) =>
    p.isCritical
      ? qora.color.systemfeedback.errorIcon
      : qora.color.systemfeedback.warningIcon};

  --qora-collapse-icon-color-hover: ${(p) =>
    p.isCritical
      ? qora.color.systemfeedback.errorIcon
      : qora.color.systemfeedback.warningIcon};

  @supports (color: color-mix(in srgb, transparent, transparent)) {
    --qora-collapse-icon-color-hover: color-mix(
      in srgb,
      var(--qora-collapse-icon-color),
      var(--qora-collapse-background-color) 50%
    );
  }

  font: ${qora.font.small.semibold};

  color: ${(p) =>
    p.isCritical
      ? qora.color.systemfeedback.errorText
      : qora.color.systemfeedback.warningText};

  & > * > li {
    font: ${qora.font.small.regular};
    margin-bottom: 8px;
  }
`

export const AlertTitle = styled.span<WarningProps & { isInfo?: boolean }>`
  margin-left: -16px; /* Remove gap from empty icon in grid */
  text-align: start;
  vertical-align: middle;
  color: ${(p) =>
    p.isInfo
      ? qora.color.systemfeedback.infoText
      : p.isCritical
        ? qora.color.systemfeedback.errorText
        : qora.color.systemfeedback.warningText};
  font: ${qora.font.small.semibold};
`

export const CollapseTitle = styled(AlertTitle)`
  margin-left: 0px;
`

export const WarningsList = styled.ul`
  margin: 0;
  max-height: 230px;
  overflow-y: scroll;
  padding: 8px 12px;

  ${styledScrollbarMixin}

  & > li {
    line-height: 18px;
    margin-left: 2%;
    margin-bottom: 14px;
  }
`

export const DismissButton = styled(Button)`
  flex-grow: 0;
`

export const FullWidth = styled.div`
  min-width: 100%;
`
