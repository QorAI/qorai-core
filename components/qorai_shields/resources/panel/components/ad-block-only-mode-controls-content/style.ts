// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import Alert from '@qorai/qora/react/alert'
import styled from 'styled-components'

export const Container = styled.div`
  padding: 0 var(--qora-spacing-xl) var(--qora-spacing-xl);
`

export const HeaderRow = styled.div`
  margin: 0 var(--qora-spacing-xl) var(--qora-spacing-xl);
  display: flex;
  align-items: center;
  gap: var(--qora-spacing-m);
`

export const HeaderTextColumn = styled.div`
  display: flex;
  flex-direction: column;
`

export const HeaderTitle = styled.div`
  font: var(--qora-font-default-regular);
  color: var(--qora-color-text-primary);
  margin-bottom: var(--qora-spacing-xs);
`

export const HeaderDescription = styled.div`
  font: var(--qora-font-small-regular);
  color: var(--qora-color-text-tertiary);
`

export const StyledAlert = styled(Alert)`
  padding: var(--qora-spacing-m) var(--qora-spacing-xl) var(--qora-spacing-xl);
`

export const ActionsSlotWrapper = styled.div`
  display: flex;
  gap: var(--qora-spacing-m);
`
