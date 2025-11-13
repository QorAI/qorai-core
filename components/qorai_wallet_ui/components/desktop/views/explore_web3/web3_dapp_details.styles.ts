// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import Dialog from '@qorai/qora/react/dialog'
import * as qora from '@qorai/qora/tokens/css/variables'

export const DappCategoryLabel = styled.div`
  display: inline-flex;
  color: ${qora.color.neutral[50]};
  font-family: Inter, 'Poppins';
  font-size: 10px;
  font-style: normal;
  font-weight: 700;
  line-height: normal;
  text-transform: uppercase;
  height: 20px;
  padding: 0px ${qora.spacing.s};
  align-items: center;
  justify-content: center;
  gap: ${qora.spacing.xs};
  border-radius: ${qora.radius.s};
  background: ${qora.color.neutral[20]};
  vertical-align: middle;
`

export const DappMetricContainer = styled.div`
  display: flex;
  flex: 1;
  flex-direction: column;
  align-items: flex-start;
  justify-content: center;
  gap: ${qora.spacing.s};
  padding: ${qora.spacing.xl};
  border-radius: ${qora.radius.m};
  border: 1px solid ${qora.color.divider.subtle};
`

export const DappDetailDialog = styled(Dialog)`
  --qora-dialog-backdrop-background: rgba(17, 18, 23, 0.35);
  --qora-dialog-backdrop-filter: blur(8px);
  --qora-dialog-padding: ${qora.spacing['3Xl']};
`

export const Title = styled.h1`
  color: ${qora.color.text.primary};
  font: ${qora.font.heading.h2};
  margin: 0;
  padding: 0;
`
