// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import styled from 'styled-components'
import QoraSegmentedControl, {
  SegmentedControlProps,
} from '@qorai/qora/react/segmentedControl'

// Shared Styles
import { Title } from '../onboarding/onboarding.style'
import { Row, Text } from '../../../components/shared/style'

export const DepositTitle = styled(Title)`
  margin-top: 0px;
`

export const ControlsWrapper = styled(Row)`
  margin-bottom: 24px;
  --qora-segmented-control-width: 100%;
`

export const SegmentedControl = styled(QoraSegmentedControl).attrs({
  size: 'default',
})<SegmentedControlProps>``

export const AddressText = styled(Text)`
  word-break: break-all;
  max-width: 500px;
`
