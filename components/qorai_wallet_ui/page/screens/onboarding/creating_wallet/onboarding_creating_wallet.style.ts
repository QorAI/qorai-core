// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import styled from 'styled-components'
import ProgressRing from '@qorai/qora/react/progressRing'
import * as qora from '@qorai/qora/tokens/css/variables'

// Shared Styles
import { Text } from '../../../../components/shared/style'

export const LoadingIcon = styled(ProgressRing)`
  --qora-progressring-size: 40px;
  --qora-progressring-color: ${qora.color.icon.interactive};
  margin-bottom: 20px;
`

export const CreatingWalletText = styled(Text)`
  font-weight: 500;
  line-height: 28px;
  color: ${qora.color.text.primary};
`
