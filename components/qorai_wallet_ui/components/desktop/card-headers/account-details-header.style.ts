// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import Icon from '@qorai/qora/react/icon'

// Shared Styles
import { Text } from '../../shared/style'

export const AccountNameText = styled(Text)`
  line-height: 24px;
  color: ${qora.color.text.primary};
`

export const AddressText = styled(Text)`
  font-size: 12px;
  line-height: 18px;
  color: ${qora.color.text.primary};
  margin-right: 8px;
`

export const AccountsNetworkText = styled(Text)`
  font-size: 12px;
  line-height: 18px;
  color: ${qora.color.text.secondary};
`

export const AccountBalanceText = styled(Text)`
  font-size: 22px;
  line-height: 32px;
  font-weight: 500;
  color: ${qora.color.text.primary};
`

export const CopyIcon = styled(Icon).attrs({
  name: 'copy',
})`
  cursor: pointer;
  --qora-icon-size: 14px;
  color: ${qora.color.icon.default};
`
