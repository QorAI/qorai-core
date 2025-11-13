// Copyright (c) 2024 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Button from '@qorai/qora/react/button'

import { Row } from '../style'

export const PaginationRow = styled(Row)`
  gap: ${qora.spacing.s};
`

export const PaginationButton = styled(Button)`
  --qora-button-padding: ${qora.spacing.s};
  min-width: 36px;
  flex: 1;
`
