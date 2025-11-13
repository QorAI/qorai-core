// Copyright (c) 2025 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'

// Assets
import {
  PageNotFoundIconLight,
  PageNotFoundIconDark,
} from '../../../assets/svg-icons/page_not_found_icons'

// Shared Styles
import { Column, Text } from '../../../components/shared/style'

export const StyledWrapper = styled.div`
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  width: 100%;
  height: 100vh;
  padding: 0px 24px;
`

export const ContentWrapper = styled(Column)`
  background-color: ${qora.color.container.background};
  border-radius: ${qora.radius.xl};
  max-width: 640px;
  box-shadow:
    0px ${qora.elevation.xxs} 0px 0px ${qora.color.elevation.primary},
    0px ${qora.elevation.xxs} ${qora.elevation.xs} 0px
      ${qora.color.elevation.secondary};
`

export const Title = styled(Text)`
  font-size: 34px;
  line-height: 40px;
`

export const PageNotFoundIllustration = styled.div`
  width: 120px;
  height: 110px;
  background-image: url(${PageNotFoundIconLight});
  background-repeat: no-repeat;
  background-size: cover;
  background-position: center;
  color: green;
  margin-bottom: ${qora.spacing['2Xl']};
  @media (prefers-color-scheme: dark) {
    background-image: url(${PageNotFoundIconDark});
  }
`
