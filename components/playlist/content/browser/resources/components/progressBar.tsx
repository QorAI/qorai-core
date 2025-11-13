/* Copyright (c) 2023 The QorAI Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import styled from 'styled-components'

import QoraProgressBar from '@qorai/qora/react/progressBar'
import { color } from '@qorai/qora/tokens/css/variables'

export const ProgressBar = styled(QoraProgressBar)`
  position: absolute;
  bottom: 0;
  width: 100%;
  height: 3px;
  --qora-progressbar-radius: 0;
  --qora-progressbar-background-color: color-mix(
    in srgb,
    ${color.white} 40%,
    transparent
  );
`
