// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'

export const IntroImg = styled.img`
  width: 336px;
  height: 264px;
  margin: 0 auto;
`

export const Title = styled.h2`
  color: ${qora.color.text.primary};
  text-align: center;
  font: ${qora.font.heading.h1};
  margin: 0;
  padding: 0;
`

export const SubTitle = styled.h5`
  color: ${qora.color.text.secondary};
  text-align: center;
  font: ${qora.font.default.regular};
  font-size: 16px;
  margin: 0;
`
