// Copyright (c) 2022 The Qorai Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import * as qora from '@qorai/qora/tokens/css/variables'
import { LinkText } from '../../../../components/shared/style'

export const CheckboxText = styled.div`
  display: flex;
  flex-direction: column;
  width: 100%;
  height: 100%;
  padding: 0;

  & > p {
    margin-top: 4px;
    padding-top: 0px;
    padding-left: 14px;
    text-align: left;
    vertical-align: top;

    font: ${qora.font.large.regular};
    letter-spacing: 0.01em;

    color: ${qora.color.text.primary};
  }
`

export const TermsLink = styled(LinkText)`
  font-weight: 400;
`
