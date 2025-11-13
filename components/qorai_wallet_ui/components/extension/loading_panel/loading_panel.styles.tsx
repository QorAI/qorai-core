// Copyright (c) 2023 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import { LoaderIcon } from 'qorai-ui/components/icons'

export const LoadingMessage = styled.span`
  color: ${qora.color.text.primary};
  text-align: center;
  font: ${qora.font.small.regular};
`

export const LoadingIconWrapper = styled.div`
  position: relative;
  height: 32px;
  width: 32px;
`

export const LoadingIconBG = styled(LoaderIcon)`
  position: absolute;
  top: 0;
  bottom: 0;
  left: 0;
  right: 0;
  color: ${qora.color.container.highlight};
  z-index: 100;
  rotate: 180deg;
`

export const LoadingIconFG = styled(LoaderIcon)`
  position: absolute;
  top: 0;
  bottom: 0;
  left: 0;
  right: 0;
  color: ${qora.color.icon.interactive};
  z-index: 101;
`
