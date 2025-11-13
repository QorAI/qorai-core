// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import Alert from '@qorai/qora/react/alert'
import styled from 'styled-components'

export const Container = styled.div`
  padding: var(--qora-spacing-xl);
`

export const Title = styled.div`
  font: var(--qora-font-heading-h4);
`

export const Description = styled.div`
  font: var(--qora-font-default-regular);
  a {
    color: var(--qora-color-text-secondary);
  }
`

export const Actions = styled.div`
  padding-top: var(--qora-spacing-xl);
  display: flex;
  gap: var(--qora-spacing-m);
`

export const StyledAlert = styled(Alert)`
  padding: 0 var(--qora-spacing-xl) var(--qora-spacing-xl);
`

export const ActionsSlotWrapper = styled.div`
  display: flex;
  gap: var(--qora-spacing-m);
`
